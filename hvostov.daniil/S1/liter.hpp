#ifndef LITER_HPP
#define LITER_HPP

#include <cstddef>

namespace hvostov {

  template< class T >
  class List;
  template< class T >
  class Node;

  template< class T >
  class Liter {
  public:
    Liter() noexcept;
    Liter(Node< T >* curr, Node< T >* fake) noexcept;
    Liter< T >& operator++();
    Liter< T > operator++(int);
    T operator*();
    T operator->();
    bool operator==(const Liter< T >& liter);
    bool operator!=(const Liter< T >& liter);
    
  private:
    friend class List< T >;
    Node< T >* curr_;
    Node< T >* fake_;
  };
}

template< class T >
hvostov::Liter< T >::Liter() noexcept:
  curr_(nullptr),
  fake_(nullptr)
{}

template< class T >
hvostov::Liter< T >::Liter(Node< T >* curr, Node< T >* fake) noexcept:
  curr_(curr),
  fake_(fake)
{}

template< class T >
hvostov::Liter< T >& hvostov::Liter< T >::operator++()
{
  curr_ = curr_->next_;
  return *this;
}

template< class T >
hvostov::Liter< T > hvostov::Liter< T >::operator++(int)
{
  Liter< T > temp = *this;
  ++(*this);
  return temp;
}

template< class T >
T hvostov::Liter< T >::operator*()
{
  return curr_->val_;
}

template< class T >
T hvostov::Liter< T >::operator->()
{
  return curr_->val_;
}

template< class T >
bool hvostov::Liter< T >::operator==(const Liter< T >& liter)
{
  return curr_ == liter.curr_;
}

template< class T >
bool hvostov::Liter< T >::operator!=(const Liter< T >& liter)
{
  return curr_ != liter.curr_;
}
#endif
