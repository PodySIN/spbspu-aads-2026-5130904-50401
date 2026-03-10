#include <iostream>
#include "list.hpp"
#include "liter.hpp"
#include "lciter.hpp"
#include "utility.hpp"

int main()
{
  hvostov::List< std::pair< std::string, hvostov::List< size_t > > > list = hvostov::getData(std::cin);
  hvostov::Liter< std::pair< std::string, hvostov::List< size_t > > > it = list.begin();
  for (hvostov::Liter< std::pair< std::string, hvostov::List< size_t > > > it = list.begin(); it != list.end(); it++) {
    std::cout << (*it).first << "\n";
    hvostov::List< size_t > n = (*it).second;
    for (hvostov::Liter< size_t > j = n.begin(); j != n.end(); j++) {
      std::cout << (*j) << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
