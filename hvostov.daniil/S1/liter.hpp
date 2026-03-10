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
    Liter(Node< T >* curr) noexcept;
    Liter(const Liter< T >& liter) noexcept;
    Liter(Liter< T >&& liter) noexcept;
    Liter< T >& operator=(const Liter< T >& liter) noexcept;
    Liter< T >& operator=(Liter< T >&& liter) noexcept;
    Liter< T >& operator++();
    Liter< T > operator++(int);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const Liter< T >& liter) const;
    bool operator!=(const Liter< T >& liter) const;
    
  private:
    friend class List< T >;
    Node< T >* curr_;
  };
}

template< class T >
hvostov::Liter< T >::Liter() noexcept:
  curr_(nullptr)
{}

template< class T >
hvostov::Liter< T >::Liter(Node< T >* curr) noexcept:
  curr_(curr)
{}

template< class T >
hvostov::Liter< T >::Liter(const Liter< T >& liter) noexcept:
  curr_(liter.curr_)
{}

template< class T >
hvostov::Liter< T >::Liter(Liter< T >&& liter) noexcept:
  curr_(liter.curr_)
{
  liter.curr_ = nullptr;
}

template< class T >
hvostov::Liter< T >& hvostov::Liter< T >::operator=(const Liter< T >& liter) noexcept
{
  if (this != &liter) {
    curr_ = liter.curr_;
  }
  return *this;
}

template< class T >
hvostov::Liter< T >& hvostov::Liter< T >::operator=(Liter< T >&& liter) noexcept
{
  if (this != &liter) {
    curr_ = liter.curr_;
    liter.curr_ = nullptr;
  }
  return *this;
}

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
T& hvostov::Liter< T >::operator*() const
{
  return curr_->val_;
}

template< class T >
T* hvostov::Liter< T >::operator->() const
{
  return &(curr_->val_);
}

template< class T >
bool hvostov::Liter< T >::operator==(const Liter< T >& liter) const
{
  return curr_ == liter.curr_;
}

template< class T >
bool hvostov::Liter< T >::operator!=(const Liter< T >& liter) const
{
  return curr_ != liter.curr_;
}
#endif
