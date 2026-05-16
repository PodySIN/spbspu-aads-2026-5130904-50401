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
#endif
