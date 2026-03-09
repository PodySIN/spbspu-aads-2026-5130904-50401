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

      Liter< T > insertAfter(Liter< T > it, const T val);
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
  fake_ = static_cast< Node< T >* >(::operator new (sizeof(Node< T >*)));
  return fake_;
}

template< class T >
void hvostov::List< T >::rmFake() noexcept
{
  ::operator delete(fake_);
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
  fake_->next = fake_;
  Node< T >* head = fake_;
  for (Liter< T > it = list.begin(); it < it.end(); it++) {
    head = insertAfter(fake_, *it);
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
  Node< T >* head = fake_;
  for (Liter< T > it = list.begin(); it < it.end(); it++) {
    head = insertAfter(fake_, *it);
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
  return { fake_->next_, fake_ };
}

template< class T >
hvostov::Liter< T > hvostov::List< T >::end() const noexcept
{
  return { fake_, fake_ };
}

template< class T >
hvostov::Liter< T > hvostov::List< T >::insertAfter(Liter< T > i, const T val)
{
  Node< T >* new_node = new Node< T >{ val, i.curr_->next_ };
  i.curr_->next_ = new_node;
  return { new_node, fake_ };
}

template< class T >
void hvostov::List< T >::clear()
{
  while (fake_ != fake_) {
    Node< T >* tmp = fake_->next_;
    delete fake_;
    fake_ = tmp;
  }
  fake_->next_ = fake_;
}
#endif
