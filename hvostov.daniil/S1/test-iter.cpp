#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(iter_suite)

BOOST_AUTO_TEST_CASE(test_begin)
{
  hvostov::List< size_t > list;
  list.pushBack(6);
  list.pushBack(7);
  hvostov::Liter< size_t > it = list.begin();
  BOOST_CHECK(*it == 6);
}

BOOST_AUTO_TEST_CASE(test_end)
{
  hvostov::List< size_t > list;
  list.pushBack(6);
  list.pushBack(7);
  hvostov::Liter< size_t > it = list.end();
  BOOST_CHECK(*it == 7);
}

BOOST_AUTO_TEST_SUITE_END()
