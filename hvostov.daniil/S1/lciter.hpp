#ifndef LCITER_HPP
#define LCITER_HPP

#include <cstddef>

namespace hvostov {

  template< class T >
  class List;
  template< class T >
  class Node;

  template< class T >
  class LCiter {
  public:
    LCiter() noexcept;
    LCiter(Node< T >* curr) noexcept;
    LCiter(const LCiter< T >& lciter) noexcept;
    LCiter(LCiter< T >&& lciter) noexcept;
    LCiter< T >& operator=(const LCiter< T >& lciter) noexcept;
    LCiter< T >& operator=(LCiter< T >&& lciter) noexcept;
    LCiter< T >& operator++();
    LCiter< T > operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    bool operator==(const LCiter< T >& lciter) const;
    bool operator!=(const LCiter< T >& lciter) const;
    
  private:
    friend class List< T >;
    Node< T >* curr_;
  };
}

template< class T >
hvostov::LCiter< T >::LCiter() noexcept:
  curr_(nullptr)
{}

template< class T >
hvostov::LCiter< T >::LCiter(Node< T >* curr) noexcept:
  curr_(curr)
{}

template< class T >
hvostov::LCiter< T >::LCiter(const LCiter< T >& lciter) noexcept:
  curr_(lciter.curr_)
{}

template< class T >
hvostov::LCiter< T >::LCiter(LCiter< T >&& lciter) noexcept:
  curr_(lciter.curr_)
{
  lciter.curr_ = nullptr;
}

template< class T >
hvostov::LCiter< T >& hvostov::LCiter< T >::operator=(const LCiter< T >& lciter) noexcept
{
  if (this != &lciter) {
    curr_ = lciter.curr_;
  }
  return *this;
}

template< class T >
hvostov::LCiter< T >& hvostov::LCiter< T >::operator=(LCiter< T >&& lciter) noexcept
{
  if (this != &lciter) {
    curr_ = lciter.curr_;
    lciter.curr_ = nullptr;
  }
  return *this;
}

template< class T >
hvostov::LCiter< T >& hvostov::LCiter< T >::operator++()
{
  curr_ = curr_->next_;
  return *this;
}

template< class T >
hvostov::LCiter< T > hvostov::LCiter< T >::operator++(int)
{
  LCiter< T > temp = *this;
  ++(*this);
  return temp;
}

template< class T >
const T& hvostov::LCiter< T >::operator*() const
{
  return curr_->val_;
}

template< class T >
const T* hvostov::LCiter< T >::operator->() const
{
  return &(curr_->val_);
}

template< class T >
bool hvostov::LCiter< T >::operator==(const LCiter< T >& lciter) const
{
  return curr_ == lciter.curr_;
}

template< class T >
bool hvostov::LCiter< T >::operator!=(const LCiter< T >& lciter) const
{
  return curr_ != lciter.curr_;
}
#endif

