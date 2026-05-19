#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>
#include <cstddef>
#include <utility>

namespace hvostov {
  namespace detail {
    template < class T >
    struct Node {
      T val;
      Node< T >* next;
    };
  }

  template < class T >
  class List;

  template < class T >
  class Liter {
  public:
    Liter() = default;
    Liter(const Liter< T >& liter) = default;
    Liter(Liter< T >&& liter) noexcept = default;
    Liter< T >& operator=(const Liter< T >& liter) = default;
    Liter< T >& operator=(Liter< T >&& liter) noexcept = default;
    Liter< T >& operator++() noexcept;
    Liter< T > operator++(int);
    T& operator*() noexcept;
    T* operator->() noexcept;
    bool operator==(const Liter< T >& liter) const noexcept;
    bool operator!=(const Liter< T >& liter) const noexcept;

  private:
    friend class List< T >;
    detail::Node< T >* curr_;
    Liter(detail::Node< T >* n);
  };

  template < class T >
  class LCiter {
  public:
    LCiter() = default;
    LCiter(const LCiter< T >& lciter) = default;
    LCiter(LCiter< T >&& lciter) noexcept = default;
    LCiter< T >& operator=(const LCiter< T >& lciter) = default;
    LCiter< T >& operator=(LCiter< T >&& lciter) noexcept = default;
    LCiter< T >& operator++() noexcept;
    LCiter< T > operator++(int);
    const T& operator*() const noexcept;
    const T* operator->() const noexcept;
    bool operator==(const LCiter< T >& lciter) const noexcept;
    bool operator!=(const LCiter< T >& lciter) const noexcept;

  private:
    friend class List< T >;
    detail::Node< T >* curr_;
    LCiter(detail::Node< T >* n);
  };

  template < class T >
  class List {
  public:
    List();
    List(const List< T >& list);
    List(List< T >&& list) noexcept;
    ~List();
    List< T >& operator=(const List< T >& list);
    List< T >& operator=(List< T >&& list) noexcept;

    Liter< T > begin() noexcept;
    Liter< T > end() noexcept;
    LCiter< T > begin() const noexcept;
    LCiter< T > end() const noexcept;
    LCiter< T > cend() const noexcept;
    LCiter< T > cbegin() const noexcept;

    Liter< T > insertAfter(const Liter< T > it, const T& val);
    Liter< T > insertAfter(const Liter< T > it, T&& val);
    void pushFront(const T& val);
    void pushFront(T&& val);
    void eraseAfter(const Liter< T > it);
    void swap(List< T >& list) noexcept;
    void clear();
    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    detail::Node< T >* fake_;
    size_t size_;
    detail::Node< T >* createFake();
    void rmFake() noexcept;
  };
}

template < class T >
hvostov::detail::Node< T >* hvostov::List< T >::createFake()
{
  return new detail::Node< T >();
}

template < class T >
void hvostov::List< T >::rmFake() noexcept
{
  if (fake_) {
    delete fake_;
    fake_ = nullptr;
  }
}

template < class T >
hvostov::Liter< T >::Liter(detail::Node< T >* n) :
  curr_(n)
{
}

template < class T >
hvostov::LCiter< T >::LCiter(detail::Node< T >* n) :
  curr_(n)
{
}

template < class T >
void hvostov::List< T >::swap(List< T >& list) noexcept
{
  std::swap(fake_, list.fake_);
  std::swap(size_, list.size_);
}
template < class T >
hvostov::LCiter< T > hvostov::List< T >::begin() const noexcept
{
  if (fake_ == nullptr) {
    return {nullptr};
  }
  return {fake_->next};
}

template < class T >
hvostov::LCiter< T > hvostov::List< T >::end() const noexcept
{
  if (fake_ == nullptr) {
    return {nullptr};
  }
  return {fake_};
}

template < class T >
hvostov::List< T >::List() :
  fake_(createFake()),
  size_(0)
{
  fake_->next = fake_;
}

template < class T >
hvostov::List< T >::List(const List< T >& list) :
  fake_(createFake()),
  size_(0)
{
  fake_->next = fake_;
  Liter< T > mit = begin();
  for (LCiter< T > it = list.begin(); it != list.end(); it++) {
    try {
      mit = insertAfter(mit, *it);
    } catch (...) {
      clear();
      rmFake();
      throw;
    }
  }
}

template < class T >
hvostov::List< T >::List(List< T >&& list) noexcept :
  fake_(std::exchange(list.fake_, nullptr)),
  size_(std::exchange(list.size_, 0))
{
}

template < class T >
hvostov::List< T >::~List()
{
  clear();
  rmFake();
}

template < class T >
hvostov::List< T >& hvostov::List< T >::operator=(const List< T >& list)
{
  assert(this != &list && "self-assignment detected");
  List< T > cpy(list);
  swap(cpy);
  return *this;
}

template < class T >
hvostov::List< T >& hvostov::List< T >::operator=(List< T >&& list) noexcept
{
  assert(this != &list && "self-assignment detected");
  clear();
  rmFake();
  fake_ = list.fake_;
  list.fake_ = nullptr;
  size_ = list.size_;
  return *this;
}

template < class T >
hvostov::Liter< T > hvostov::List< T >::begin() noexcept
{
  return {fake_->next};
}

template < class T >
hvostov::Liter< T > hvostov::List< T >::end() noexcept
{
  return {fake_};
}

template < class T >
hvostov::Liter< T > hvostov::List< T >::insertAfter(const Liter< T > it, const T& val)
{
  detail::Node< T >* n = new detail::Node< T >{val, it.curr_->next};
  it.curr_->next = n;
  size_++;
  return {n};
}

template < class T >
hvostov::Liter< T > hvostov::List< T >::insertAfter(const Liter< T > it, T&& val)
{
  detail::Node< T >* n = new detail::Node< T >{val, it.curr_->next};
  it.curr_->next = n;
  size_++;
  return {n};
}

template < class T >
void hvostov::List< T >::pushFront(const T& val)
{
  insertAfter(fake_, val);
}

template < class T >
void hvostov::List< T >::pushFront(T&& val)
{
  insertAfter(fake_, val);
}

template < class T >
void hvostov::List< T >::eraseAfter(const Liter< T > it)
{
  if (it.curr_->next != fake_) {
    detail::Node< T >* d = it.curr_->next;
    it.curr_->next = d->next;
    size_--;
    delete d;
  }
}

template < class T >
void hvostov::List< T >::clear()
{
  if (fake_ == nullptr) {
    return;
  }
  detail::Node< T >* h = fake_->next;
  while (h != fake_) {
    detail::Node< T >* temp = h->next;
    delete h;
    h = temp;
  }
  size_ = 0;
  fake_->next = fake_;
}

template < class T >
size_t hvostov::List< T >::size() const noexcept
{
  if (fake_ == nullptr) {
    return 0;
  }
  return size_;
}

template < class T >
bool hvostov::List< T >::empty() const noexcept
{
  if (fake_ == nullptr) {
    return true;
  }
  return fake_->next == fake_;
}

template < class T >
hvostov::LCiter< T > hvostov::List< T >::cend() const noexcept
{
  if (fake_ == nullptr) {
    return {nullptr};
  }
  return {fake_};
}

template < class T >
hvostov::LCiter< T > hvostov::List< T >::cbegin() const noexcept
{
  if (fake_ == nullptr) {
    return {nullptr};
  }
  return {fake_->next};
}

template < class T >
hvostov::Liter< T >& hvostov::Liter< T >::operator++() noexcept
{
  curr_ = curr_->next;
  return *this;
}

template < class T >
hvostov::Liter< T > hvostov::Liter< T >::operator++(int)
{
  Liter< T > temp = *this;
  ++(*this);
  return temp;
}

template < class T >
T& hvostov::Liter< T >::operator*() noexcept
{
  return curr_->val;
}

template < class T >
T* hvostov::Liter< T >::operator->() noexcept
{
  return std::addressof(curr_->val);
}

template < class T >
bool hvostov::Liter< T >::operator==(const Liter< T >& liter) const noexcept
{
  return curr_ == liter.curr_;
}

template < class T >
bool hvostov::Liter< T >::operator!=(const Liter< T >& liter) const noexcept
{
  return curr_ != liter.curr_;
}

template < class T >
hvostov::LCiter< T >& hvostov::LCiter< T >::operator++() noexcept
{
  curr_ = curr_->next;
  return *this;
}

template < class T >
hvostov::LCiter< T > hvostov::LCiter< T >::operator++(int)
{
  LCiter< T > temp = *this;
  ++(*this);
  return temp;
}

template < class T >
const T& hvostov::LCiter< T >::operator*() const noexcept
{
  return curr_->val;
}

template < class T >
const T* hvostov::LCiter< T >::operator->() const noexcept
{
  return std::addressof(curr_->val);
}

template < class T >
bool hvostov::LCiter< T >::operator==(const LCiter< T >& lciter) const noexcept
{
  return curr_ == lciter.curr_;
}

template < class T >
bool hvostov::LCiter< T >::operator!=(const LCiter< T >& lciter) const noexcept
{
  return curr_ != lciter.curr_;
}

#endif
