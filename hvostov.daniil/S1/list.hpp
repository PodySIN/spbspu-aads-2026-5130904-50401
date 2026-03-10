#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace hvostov {
  template< class T >
  struct Node {
    T val_;
    Node< T >* next_;
  };
  template< class T >
  class Liter;
  template< class T >
  class LCiter;

  template< class T >
  class List {
    public:
      List();
      List(const List< T >& list);
      List(List< T >&& list);
      ~List();
      List< T >& operator=(const List< T >& list);
      List< T >& operator=(List< T >&& list);

      Liter< T > begin() const noexcept;
      Liter< T > end() const noexcept;
      LCiter< T > cend() const noexcept;
      LCiter< T > cbegin() const noexcept;

      Liter< T > insertAfter(Liter< T > it, const T& val);
      void clear();
    private:
      Node< T >* fake_;
      Node< T >* createFake();
      void rmFake() noexcept;
  };
}

template< class T >
hvostov::Node< T >* hvostov::List< T >::createFake()
{
  fake_ = new Node< T >();
  return fake_;
}

template< class T >
void hvostov::List< T >::rmFake() noexcept
{
  delete fake_;
}

template< class T >
hvostov::List< T >::List():
  fake_(nullptr)
{
  createFake();
  fake_->next_ = fake_;
}

template< class T >
hvostov::List< T >::List(const List< T >& list):
  fake_(nullptr)
{
  createFake();
  fake_->next_ = fake_;
  Liter< T > i = begin();
  for (Liter< T > it = list.begin(); it != list.end(); it++) {
    i = insertAfter(i, *it);
  }
}

template< class T >
hvostov::List< T >::List(List< T >&& list):
  fake_(list.fake_)
{
  list.fake_ = nullptr;
}

template< class T >
hvostov::List< T >::~List()
{
  clear();
  rmFake();
}

template< class T >
hvostov::List< T >& hvostov::List< T >::operator=(const List< T >& list)
{
  
  if (this == &list) {
    return *this;
  }
  clear();
  Liter< T > i = begin();
  for (Liter< T > it = list.begin(); it != list.end(); it++) {
    i = insertAfter(i, *it);
  }
  return *this;
}

template< class T >
hvostov::List< T >& hvostov::List< T >::operator=(List< T >&& list)
{
  if (this == &list) {
    return *this;
  }
  clear();
  rmFake();
  fake_ = list.fake_;
  list.fake_ = nullptr;
  return *this;
}

template< class T >
hvostov::Liter< T > hvostov::List< T >::begin() const noexcept
{
  return { fake_->next_ };
}

template< class T >
hvostov::Liter< T > hvostov::List< T >::end() const noexcept
{
  return { fake_ };
}

template< class T >
hvostov::Liter< T > hvostov::List< T >::insertAfter(Liter< T > it, const T& val)
{
  Node< T >* n = new Node< T >{val, it.curr_->next_};
  it.curr_->next_ = n;
  return { n };
}

template< class T >
void hvostov::List< T >::clear()
{
  Node< T >* h = fake_->next_;
  while (h != fake_) {
    Node< T >* temp = h->next_;
    delete h;
    h = temp;
  }
  fake_->next_ = fake_;
}
#endif
