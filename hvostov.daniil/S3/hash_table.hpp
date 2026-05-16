#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "sip_hash.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace hvostov {

  template < class Key, class Value, class Hash = SipHash< Key >, class Equal = std::equal_to< Key > >
  class HashTable {
  public:
    using Iterator = HashTableIterator< Key, Value >;
    using ConstIterator = HashTableConstIterator< Key, Value >;

    HashTable() = default;
    explicit HashTable(size_t expected_elements);
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable();

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    Value& operator[](const Key& k);
    const Value& operator[](const Key& k) const;

    void swap(HashTable& other) noexcept;
    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k) const;
    void rehash(size_t new_bucket_count);
    void clear() noexcept;

    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    bool empty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    size_t bucket_size_ = 4;

    std::pair< Key, Value >* data_ = nullptr;
    size_t* bucket_sizes_ = nullptr;
    size_t bucket_count_ = 0;
    size_t overflow_cap_ = 0;
    size_t overflow_size_ = 0;
    size_t size_ = 0;

    Hash hasher_;
    Equal equal_;

    friend class HashTableIterator< Key, Value >;
    friend class HashTableConstIterator< Key, Value >;

    size_t overflowStart() const noexcept;
    size_t totalCapacity() const noexcept;

    size_t getElementIndex(const Key& k) const;
    void unsafeAdd(const Key& k, const Value& v);
    void removeByIndex(size_t index);
    void allocate(size_t num_buckets);
  };

}

template < class Key, class Value, class Hash, class Equal >
size_t hvostov::HashTable< Key, Value, Hash, Equal >::overflowStart() const noexcept
{
  return bucket_count_ * bucket_size_;
}

template < class Key, class Value, class Hash, class Equal >
size_t hvostov::HashTable< Key, Value, Hash, Equal >::totalCapacity() const noexcept
{
  return overflowStart() + overflow_cap_;
}

template < class Key, class Value, class Hash, class Equal >
void hvostov::HashTable< Key, Value, Hash, Equal >::allocate(size_t num_buckets)
{
  size_t new_bucket_count = num_buckets;
  size_t new_overflow_cap = std::max(size_t(4), num_buckets / 2);
  size_t new_total_size = new_bucket_count * bucket_size_ + new_overflow_cap;

  std::pair< Key, Value >* new_data = new std::pair< Key, Value >[new_total_size];
  try {
    size_t* new_bucket_sizes = new size_t[new_bucket_count]();

    delete[] data_;
    delete[] bucket_sizes_;

    data_ = new_data;
    bucket_sizes_ = new_bucket_sizes;
    bucket_count_ = new_bucket_count;
    overflow_cap_ = new_overflow_cap;
    size_ = 0;
    overflow_size_ = 0;

  } catch (...) {
    delete[] new_data;
    throw;
  }
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >::HashTable(size_t expected_elements) :
  bucket_size_(4),
  hasher_(),
  equal_()
{
  if (expected_elements == 0) {
    return;
  }
  constexpr double default_load_factor = 0.7;
  size_t needed_capacity = static_cast< size_t >(std::ceil(expected_elements / default_load_factor));
  if (needed_capacity <= bucket_size_) {
    bucket_count_ = 1;
  } else {
    bucket_count_ = needed_capacity / bucket_size_;
  }
  allocate(bucket_count_);
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other) :
  bucket_size_(other.bucket_size_),
  bucket_count_(other.bucket_count_),
  overflow_cap_(other.overflow_cap_),
  overflow_size_(other.overflow_size_),
  size_(other.size_),
  hasher_(other.hasher_),
  equal_(other.equal_)
{
  if (other.bucket_count_ == 0) {
    data_ = nullptr;
    bucket_sizes_ = nullptr;
    return;
  }
  size_t total_size = overflowStart() + overflow_cap_;
  std::pair< Key, Value >* new_data = new std::pair< Key, Value >[total_size];
  try {
    size_t* new_bucket_sizes = new size_t[bucket_count_];
    for (size_t i = 0; i < total_size; ++i) {
      new_data[i] = other.data_[i];
    }
    for (size_t i = 0; i < bucket_count_; ++i) {
      new_bucket_sizes[i] = other.bucket_sizes_[i];
    }
    data_ = new_data;
    bucket_sizes_ = new_bucket_sizes;
  } catch (...) {
    delete[] new_data;
    throw;
  }
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >::HashTable(HashTable&& other) noexcept :
  bucket_size_(other.bucket_size_),
  data_(other.data_),
  bucket_sizes_(other.bucket_sizes_),
  bucket_count_(other.bucket_count_),
  overflow_cap_(other.overflow_cap_),
  overflow_size_(other.overflow_size_),
  size_(other.size_),
  hasher_(std::move(other.hasher_)),
  equal_(std::move(other.equal_))
{
  other.data_ = nullptr;
  other.bucket_sizes_ = nullptr;
  other.bucket_count_ = 0;
  other.overflow_cap_ = 0;
  other.overflow_size_ = 0;
  other.size_ = 0;
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >::~HashTable()
{
  delete[] data_;
  delete[] bucket_sizes_;
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >&
hvostov::HashTable< Key, Value, Hash, Equal >::operator=(const HashTable& other)
{
  if (this == std::addressof(other)) {
    return *this;
  }
  HashTable tmp(other);
  swap(tmp);
  return *this;
}

template < class Key, class Value, class Hash, class Equal >
hvostov::HashTable< Key, Value, Hash, Equal >&
hvostov::HashTable< Key, Value, Hash, Equal >::operator=(HashTable&& other) noexcept
{
  if (this == std::addressof(other)) {
    return *this;
  }
  delete[] data_;
  delete[] bucket_sizes_;

  bucket_size_ = other.bucket_size_;
  data_ = other.data_;
  bucket_sizes_ = other.bucket_sizes_;
  bucket_count_ = other.bucket_count_;
  overflow_cap_ = other.overflow_cap_;
  overflow_size_ = other.overflow_size_;
  size_ = other.size_;
  hasher_ = std::move(other.hasher_);
  equal_ = std::move(other.equal_);

  other.data_ = nullptr;
  other.bucket_sizes_ = nullptr;
  other.bucket_count_ = 0;
  other.overflow_cap_ = 0;
  other.overflow_size_ = 0;
  other.size_ = 0;
  return *this;
}

#endif
