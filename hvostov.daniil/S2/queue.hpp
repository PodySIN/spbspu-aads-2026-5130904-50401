#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include "list.hpp"

namespace hvostov {
  template< class T >
  class Queue {
    public:
      Queue();
      Queue(const Queue< T >& queue);
      Queue(Queue< T >&& queue);
      ~Queue() = default;
      Queue< T >& operator=(const Queue< T >& queue);
      Queue< T >& operator=(Queue< T >&& queue) noexcept;

      void pop() noexcept;
      void push(T rhs);
      void clear() noexcept;
      bool empty() const noexcept;
      T drop() const;
    private:
      List< T > list_;
      LIter< T > tail_;
  };
}

template< class T >
hvostov::Queue< T >::Queue():
  list()
{}

template< class T >
hvostov::Queue< T >::Queue(const Queue< T >& queue):
  list_(queue.list_)
{
  tail_ = list_.begin();

}

template< class T >
hvostov::Queue< T >::Queue(Queue< T >&& queue):
  list(std::move(queue.list))
{}

template< class T >
hvostov::Queue< T >& hvostov::Queue< T >::operator=(const Queue< T >& queue)
{
  if (this == &queue) {
    return *this;
  }
  list = queue.list;
  return *this;
}

template< class T >
hvostov::Queue< T >& hvostov::Queue< T >::operator=(Queue< T >&& queue)
{
  if (this == &queue) {
    return *this;
  }
  list = std::move(queue.list);
  return *this;
}
#endif
