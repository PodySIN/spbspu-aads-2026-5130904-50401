#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(list_suite)

BOOST_AUTO_TEST_CASE(test_create_list)
{
  hvostov::List< int > list;
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_create_list_with_values)
{
  hvostov::List< int > list1;
  hvostov::List< int > list2(list1);
  BOOST_CHECK(list2.empty());
}

BOOST_AUTO_TEST_CASE(test_insert_element)
{
  hvostov::List< int > list;
  hvostov::Liter< int > it = list.begin();
  it = list.insertAfter(it, 6);
  BOOST_CHECK(*it == 6);
  it = list.insertAfter(it, 7);
  BOOST_CHECK(*it == 7);
  it = list.begin();
  list.insertAfter(it, 10);
  BOOST_CHECK(*it == 6);
  it++;
  BOOST_CHECK(*it == 10);
  it++;
  BOOST_CHECK(*it == 7);
  it = list.end();
  list.insertAfter(it, 8);
  it++;
  BOOST_CHECK(*it == 8);
  it++;
  BOOST_CHECK(*it == 6);
}

BOOST_AUTO_TEST_CASE(test_push_front)
{
  hvostov::List< int > list;
  list.pushFront(5);
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(*list.begin(), 5);

  list.pushFront(3);
  BOOST_CHECK_EQUAL(list.size(), 2);
  hvostov::Liter< int > it = list.begin();
  BOOST_CHECK_EQUAL(*it, 3);
  it++;
  BOOST_CHECK_EQUAL(*it, 5);

  list.pushFront(1);
  BOOST_CHECK_EQUAL(list.size(), 3);
  it = list.begin();
  BOOST_CHECK_EQUAL(*it, 1);
  it++;
  BOOST_CHECK_EQUAL(*it, 3);
  it++;
  BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(test_erase_element)
{
  hvostov::List< int > list;
  hvostov::Liter< int > it = list.begin();
  it = list.insertAfter(it, 6);
  it = list.insertAfter(it, 7);
  it = list.begin();
  list.eraseAfter(it);
  it++;
  BOOST_CHECK(!list.empty());
  BOOST_CHECK(it == list.end());
  it = list.begin();
  BOOST_CHECK((*it) == 6);
}

BOOST_AUTO_TEST_CASE(test_erase_last_element)
{
  hvostov::List< int > list;
  list.pushFront(10);
  BOOST_CHECK_EQUAL(list.size(), 1);

  hvostov::Liter< int > it = list.end();
  list.eraseAfter(it);
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_erase_middle_element)
{
  hvostov::List< int > list;
  list.pushFront(10);
  list.pushFront(20);
  list.pushFront(30);

  hvostov::Liter< int > it = list.end();
  it++;
  list.eraseAfter(it);

  hvostov::Liter< int > check = list.begin();
  BOOST_CHECK_EQUAL(*check, 30);
  check++;
  BOOST_CHECK_EQUAL(*check, 10);
  check++;
  BOOST_CHECK(check == list.end());
  BOOST_CHECK_EQUAL(list.size(), 2);
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  hvostov::List< int > list;
  hvostov::Liter< int > it = list.begin();
  it = list.insertAfter(it, 6);
  it = list.insertAfter(it, 7);
  it = list.insertAfter(it, 6);
  it = list.insertAfter(it, 7);
  BOOST_CHECK(!list.empty());
  BOOST_CHECK_EQUAL(list.size(), 4);
  list.clear();
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
  it = list.begin();
  it = list.insertAfter(it, 6);
  it = list.insertAfter(it, 7);
  BOOST_CHECK(!list.empty());
  BOOST_CHECK_EQUAL(list.size(), 2);
  list.clear();
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  hvostov::List< int > list1;
  list1.pushFront(10);
  list1.pushFront(20);
  list1.pushFront(30);

  hvostov::List< int > list2(list1);

  BOOST_CHECK_EQUAL(list2.size(), list1.size());

  hvostov::Liter< int > it1 = list1.begin();
  hvostov::Liter< int > it2 = list2.begin();

  while (it1 != list1.end() && it2 != list2.end()) {
    BOOST_CHECK_EQUAL(*it1, *it2);
    ++it1;
    ++it2;
  }

  BOOST_CHECK(it1 == list1.end());
  BOOST_CHECK(it2 == list2.end());
}

BOOST_AUTO_TEST_CASE(test_copy_constructor_empty)
{
  hvostov::List< int > list1;
  hvostov::List< int > list2(list1);

  BOOST_CHECK(list2.empty());
  BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_copy_assignment)
{
  hvostov::List< int > list1;
  list1.pushFront(10);
  list1.pushFront(20);
  list1.pushFront(30);

  hvostov::List< int > list2;
  list2.pushFront(100);
  list2 = list1;

  BOOST_CHECK_EQUAL(list2.size(), list1.size());

  hvostov::Liter< int > it1 = list1.begin();
  hvostov::Liter< int > it2 = list2.begin();

  while (it1 != list1.end() && it2 != list2.end()) {
    BOOST_CHECK_EQUAL(*it1, *it2);
    ++it1;
    ++it2;
  }
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  hvostov::List< int > list1;
  list1.pushFront(10);
  list1.pushFront(20);
  list1.pushFront(30);

  size_t old_size = list1.size();

  hvostov::List< int > list2(std::move(list1));

  BOOST_CHECK_EQUAL(list2.size(), old_size);
  BOOST_CHECK_EQUAL(list1.empty(), true);

  hvostov::Liter< int > it = list2.begin();
  BOOST_CHECK_EQUAL(*it, 30);
  ++it;
  BOOST_CHECK_EQUAL(*it, 20);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
}

BOOST_AUTO_TEST_CASE(test_move_assignment)
{
  hvostov::List< int > list1;
  list1.pushFront(10);
  list1.pushFront(20);
  list1.pushFront(30);

  hvostov::List< int > list2;
  list2.pushFront(100);

  size_t old_size = list1.size();
  list2 = std::move(list1);

  BOOST_CHECK_EQUAL(list2.size(), old_size);
  BOOST_CHECK(list1.empty());

  hvostov::Liter< int > it = list2.begin();
  BOOST_CHECK_EQUAL(*it, 30);
  ++it;
  BOOST_CHECK_EQUAL(*it, 20);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  hvostov::List< int > list1;
  list1.pushFront(10);
  list1.pushFront(20);

  hvostov::List< int > list2;
  list2.pushFront(30);
  list2.pushFront(40);
  list2.pushFront(50);

  size_t size1 = list1.size();
  size_t size2 = list2.size();

  list1.swap(list2);

  BOOST_CHECK_EQUAL(list1.size(), size2);
  BOOST_CHECK_EQUAL(list2.size(), size1);

  hvostov::Liter< int > it = list1.begin();
  BOOST_CHECK_EQUAL(*it, 50);
  ++it;
  BOOST_CHECK_EQUAL(*it, 40);
  ++it;
  BOOST_CHECK_EQUAL(*it, 30);

  it = list2.begin();
  BOOST_CHECK_EQUAL(*it, 20);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
}

BOOST_AUTO_TEST_CASE(test_empty)
{
  hvostov::List< int > list;
  BOOST_CHECK(list.empty());

  list.pushFront(5);
  BOOST_CHECK(!list.empty());

  list.clear();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_size)
{
  hvostov::List< int > list;
  BOOST_CHECK_EQUAL(list.size(), 0);

  list.pushFront(1);
  BOOST_CHECK_EQUAL(list.size(), 1);

  list.pushFront(2);
  BOOST_CHECK_EQUAL(list.size(), 2);

  list.pushFront(3);
  BOOST_CHECK_EQUAL(list.size(), 3);

  hvostov::Liter< int > it = list.begin();
  list.eraseAfter(it);
  BOOST_CHECK_EQUAL(list.size(), 2);

  list.clear();
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_iterator_increment)
{
  hvostov::List< int > list;
  list.pushFront(10);
  list.pushFront(20);
  list.pushFront(30);

  hvostov::Liter< int > it = list.begin();
  BOOST_CHECK_EQUAL(*it, 30);

  hvostov::Liter< int > it2 = it++;
  BOOST_CHECK_EQUAL(*it2, 30);
  BOOST_CHECK_EQUAL(*it, 20);

  ++it;
  BOOST_CHECK_EQUAL(*it, 10);

  ++it;
  BOOST_CHECK(it == list.end());
}

BOOST_AUTO_TEST_CASE(test_const_iterator)
{
  hvostov::List< int > list;
  list.pushFront(10);
  list.pushFront(20);
  list.pushFront(30);

  const hvostov::List< int >& const_list = list;

  hvostov::LCiter< int > it = const_list.begin();
  BOOST_CHECK_EQUAL(*it, 30);
  ++it;
  BOOST_CHECK_EQUAL(*it, 20);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
  ++it;
  BOOST_CHECK(it == const_list.end());
}

BOOST_AUTO_TEST_CASE(test_const_iterator_copy)
{
  hvostov::List< int > list;
  list.pushFront(10);

  const hvostov::List< int >& const_list = list;

  hvostov::LCiter< int > it1 = const_list.begin();
  hvostov::LCiter< int > it2 = it1;

  BOOST_CHECK(it1 == it2);
  BOOST_CHECK_EQUAL(*it1, *it2);
}

BOOST_AUTO_TEST_CASE(test_begin_end_consistency)
{
  hvostov::List< int > list;
  BOOST_CHECK(list.begin() == list.end());

  list.pushFront(5);
  BOOST_CHECK(list.begin() != list.end());

  hvostov::Liter< int > it = list.begin();
  ++it;
  BOOST_CHECK(it == list.end());
}

BOOST_AUTO_TEST_CASE(test_insert_after_end)
{
  hvostov::List< int > list;
  hvostov::Liter< int > it = list.end();

  it = list.insertAfter(it, 10);
  BOOST_CHECK_EQUAL(*it, 10);
  BOOST_CHECK_EQUAL(list.size(), 1);

  it = list.begin();
  BOOST_CHECK_EQUAL(*it, 10);
}

BOOST_AUTO_TEST_CASE(test_complex_type)
{
  hvostov::List< std::string > list;
  list.pushFront("hello");
  list.pushFront("world");

  BOOST_CHECK_EQUAL(list.size(), 2);

  hvostov::Liter< std::string > it = list.begin();
  BOOST_CHECK_EQUAL(*it, "world");
  ++it;
  BOOST_CHECK_EQUAL(*it, "hello");
}

BOOST_AUTO_TEST_SUITE_END()
