#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(iter_suite)

BOOST_AUTO_TEST_CASE(test_begin)
{
  hvostov::List< int > list;
  list.pushBack(6);
  list.pushBack(7);
  hvostov::Liter< int > it = list.begin();
  BOOST_CHECK(*it == 6);
}

BOOST_AUTO_TEST_CASE(test_end)
{
  hvostov::List< int > list;
  list.pushBack(6);
  list.pushBack(7);
  hvostov::Liter< int > it = list.end();
  BOOST_CHECK(*it != 7);
  it++;
  BOOST_CHECK(*it == 6);
}

BOOST_AUTO_TEST_SUITE_END()
