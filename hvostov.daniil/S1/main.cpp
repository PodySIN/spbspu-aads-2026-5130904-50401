#include <iostream>
#include "list.hpp"
#include "utility.hpp"

int main()
{
  hvostov::List< std::pair< std::string, hvostov::List< size_t > > > list;
  try {
    list = hvostov::getData(std::cin);
  } catch (const std::overflow_error& e) {
    try {
      hvostov::printResult(std::cout, list);
    } catch (const std::overflow_error& e) {
      std::cerr << e.what() << "\n";
      return 1;
    }
    std::cerr << e.what() << "\n";
    return 1;
  }
  if (list.empty()) {
    std::cout << "0\n";
    return 0;
  }
  try {
    hvostov::printResult(std::cout, list);
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
