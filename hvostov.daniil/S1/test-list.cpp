#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(list_suite)

BOOST_AUTO_TEST_CASE(test_create_list)
{
  List< size_t > list;
  BOOST_CHECK(list.empty()); }

BOOST_AUTO_TEST_CASE(test_push_element)
{
  List< size_t > list;
  list.pushBack(6);
  BOOST_CHECK(list.empty());
  BOOST_CHECK(*(list.end()) == 6);
}

BOOST_AUTO_TEST_CASE(test_insert_element)
{
  List< size_t > list;
  Liter< T > it = list.begin();
  it = insertAfter(it, 6);
  BOOST_CHECK(*it == 6);
  it = insertAfter(it, 7);
  BOOST_CHECK(*it == 7);
  it = list.begin();
  insertAfter(it, 10);
  BOOST_CHECK(*it == 6);
  it++;
  BOOST_CHECK(*it == 10);
  it++;
  BOOST_CHECK(*it == 7);
  it = list.end();
  insertAfter(it, 8);
  BOOST_CHECK(*it == 7);
  it++;
  BOOST_CHECK(*it == 8);
  it++;
  BOOST_CHECK(it == list.end());
}

BOOST_AUTO_TEST_CASE(test_erase_element)
{
  List< size_t > list;
  list.pushBack(6);
  list.pushBack(7);
  Liter< size_t > it = list.begin();
  eraseAfter(it);
  it++;
  BOOST_CHECK(!list.empty());
  BOOST_CHECK(it == list.end());
  it = list.begin();
  BOOST_CHECK((*it) == 6);
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  List< size_t > list;
  list.pushBack(6);
  list.pushBack(7);
  list.pushBack(6);
  list.pushBack(7);
  BOOST_CHECK(!list.empty());
  list.clear();
  BOOST_CHECK(list.empty());
  list.pushBack(6);
  list.pushBack(7);
  BOOST_CHECK(!list.empty());
  list.clear();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_SUITE_END()
