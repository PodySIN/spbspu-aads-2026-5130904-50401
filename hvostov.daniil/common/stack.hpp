#ifndef stack_HPP
#define stack_HPP
#include "list.hpp"
#include <cstddef>

namespace hvostov {
  template < class T >
  class Stack {
  public:
    Stack() = default;
    Stack(const Stack< T >& stack) = default;
    Stack(Stack< T >&& stack) noexcept = default;
    ~Stack() = default;
    Stack< T >& operator=(const Stack< T >& stack) = default;
    Stack< T >& operator=(Stack< T >&& stack) noexcept = default;

    T drop();
    void push(const T& rhs);
    void push(T&& rhs);
    void clear() noexcept;
    bool empty() const noexcept;
    T& top();
    const T& top() const;
    size_t size() const noexcept;

  private:
    List< T > list_;
  };
}

template < class T >
T hvostov::Stack< T >::drop()
{
  T t = top();
  list_.eraseAfter(list_.end());
  return t;
}

template < class T >
void hvostov::Stack< T >::push(const T& rhs)
{
  list_.insertAfter(list_.end(), rhs);
}

template < class T >
void hvostov::Stack< T >::push(T&& rhs)
{
  list_.insertAfter(list_.end(), rhs);
}

template < class T >
void hvostov::Stack< T >::clear() noexcept
{
  list_.clear();
}

template < class T >
bool hvostov::Stack< T >::empty() const noexcept
{
  return list_.empty();
}

template < class T >
T& hvostov::Stack< T >::top()
{
  return *(list_.begin());
}

template < class T >
const T& hvostov::Stack< T >::top() const
{
  return *(list_.begin());
}

template < class T >
size_t hvostov::Stack< T >::size() const noexcept
{
  return list_.size();
}

#endif
