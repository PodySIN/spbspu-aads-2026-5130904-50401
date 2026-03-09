#include <iostream>
#include "list.hpp"
#include "liter.hpp"
#include "lciter.hpp"

int main()
{
  hvostov::List< int > l;
  hvostov::Liter< int > it = l.begin();
  for (size_t i = 0; i < 5; i++) {
    it = l.insertAfter(it, i);
  }
  for (hvostov::Liter< int > it = l.begin(); it != l.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}
