#ifndef stack_HPP
#define stack_HPP
#include <cstddef>
#include "list.hpp"

namespace hvostov {
  template< class T >
  class Stack {
    public:
      Stack();
      Stack(const Stack< T >& stack);
      Stack(Stack< T >&& stack);
      ~Stack();
      Stack< T >& operator=(const Stack< T >& stack);
      Stack< T >& operator=(Stack< T >&& stack) noexcept;

      void pop();
      void push(T rhs);
      void clear();
      bool empty();
      T drop();
    private:
      List< T > list_;
      Liter< T > tail_;
  };
}

#endif
