#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"
#include <cstddef>

namespace hvostov {
  template < class T >
  class Queue {
  public:
    Queue();
    Queue(const Queue< T >& queue) = default;
    Queue(Queue< T >&& queue) noexcept = default;
    ~Queue() = default;
    Queue< T >& operator=(const Queue< T >& queue) = default;
    Queue< T >& operator=(Queue< T >&& queue) noexcept = default;

    T drop();
    void push(const T& rhs);
    void push(T&& rhs);
    void clear() noexcept;
    bool empty() const noexcept;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    size_t size() const noexcept;

  private:
    List< T > list_;
    Liter< T > tail_;
  };
}

template < class T >
hvostov::Queue< T >::Queue() :
  list_(),
  tail_()
{
  tail_ = list_.begin();
}

template < class T >
T hvostov::Queue< T >::drop()
{
  T res = front();
  list_.eraseAfter(list_.end());
  if (empty()) {
    tail_ = list_.begin();
  }
  return res;
}

template < class T >
void hvostov::Queue< T >::push(const T& rhs)
{
  tail_ = list_.insertAfter(tail_, rhs);
}

template < class T >
void hvostov::Queue< T >::push(T&& rhs)
{
  tail_ = list_.insertAfter(tail_, rhs);
}

template < class T >
void hvostov::Queue< T >::clear() noexcept
{
  list_.clear();
  tail_ = list_.begin();
}

template < class T >
bool hvostov::Queue< T >::empty() const noexcept
{
  return list_.empty();
}

template < class T >
T& hvostov::Queue< T >::front()
{
  return *(list_.begin());
}

template < class T >
T& hvostov::Queue< T >::back()
{
  return *tail_;
}

template < class T >
const T& hvostov::Queue< T >::front() const
{
  return *(list_.begin());
}

template < class T >
const T& hvostov::Queue< T >::back() const
{
  return *tail_;
}

template < class T >
size_t hvostov::Queue< T >::size() const noexcept
{
  return list_.size();
}

#endif
