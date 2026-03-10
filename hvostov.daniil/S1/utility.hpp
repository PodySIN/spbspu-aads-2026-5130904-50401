#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <string>
#include "list.hpp"

namespace hvostov {
  List< std::pair< std::string, List< size_t > > > getData(std::istream& in);
  size_t stringToNumber(const std::string& str);
}

size_t hvostov::stringToNumber(const std::string& str)
{
  size_t result = 0;
  for (size_t i = 0; i < str.size(); i++) {
    result = result * 10 + (str[i] - '0');
  }
  return result;
}

hvostov::List< std::pair< std::string, hvostov::List< size_t > > > hvostov::getData(std::istream& in)
{
  List< std::pair< std::string, List< size_t > > > list;
  Liter< std::pair< std::string, List< size_t > > > list_it = list.begin();
  std::string name;
  char next = ' ';
  while (in >> name) {
    List< size_t > numbers;
    next = in.peek();
    if (next == '\n') {
      list_it = list.insertAfter(list_it, { name, numbers });
      continue;
    }
    if (next == EOF) {
      list_it = list.insertAfter(list_it, { name, numbers });
      break;
    }
    Liter< size_t > it = numbers.begin();
    std::string number;
    while (in >> number) {
      it = numbers.insertAfter(it, stringToNumber(number));
      next = in.peek();
      if (next == '\n' || next == EOF) {
        break;
      }
    }
    list_it = list.insertAfter(list_it, { name, numbers });
  }
  return list;
}

#endif
