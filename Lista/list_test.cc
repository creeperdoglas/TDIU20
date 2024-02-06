#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include "catch.hpp"
#include "List.h"

using namespace std;

TEST_CASE("Default constructor")
{
  List L{};
}

TEST_CASE("Single Insert")
{
  stringstream ss{};
  List list{};
  list.insert(5);
  ss << list;
  CHECK(ss.str() == "5");
}

TEST_CASE("Multiple Inserts")
{
  stringstream ss{};
  List list{};
  list.insert(5);
  list.insert(6);
  list.insert(7);
  list.insert(-1);
  list.insert(0);
  ss << list;
  CHECK(ss.str() == "-1 0 5 6 7");
}

TEST_CASE("Remove")
{
  stringstream ss{};
  List list{};
  list.insert(5); // 0
  list.insert(6); // 1
  list.insert(7); // 2

  list.remove(1);
  ss << list;
  CHECK(ss.str() == "5 7");

  ss.str("");
  ss.clear();
  list.remove(1);
  ss << list;
  CHECK(ss.str() == "5");

  ss.str("");
  ss.clear();
  list.remove(0);
  ss << list;
  CHECK(ss.str() == "");

  SECTION("Exception")
  {
    List list{};
    list.insert(5);
    list.insert(6);
    list.insert(7);
    CHECK_THROWS(list.remove(6));
  }
}
TEST_CASE("Initializer list")
{
  stringstream ss{};
  List list{1, 3, 2, 5, 4};
  ss << list;
  CHECK(ss.str() == "1 2 3 4 5");
}
// egentligen testas redan detta i remove, då borttagningen inte hade funkat annars, men kan testa igen
TEST_CASE("List size")
{
  List list{};
  CHECK(list.size() == 0);
  list.insert(5);
  CHECK(list.size() == 1);
  list.insert(6);
  CHECK(list.size() == 2);
  list.insert(7);
  CHECK(list.size() == 3);
  list.remove(1);
  CHECK(list.size() == 2);
  list.remove(1);
  CHECK(list.size() == 1);
  list.remove(0);
  CHECK(list.size() == 0);
}

TEST_CASE("Copy constructor")
{
  stringstream ss{};
  List list{};
  list.insert(5);
  list.insert(7);
  list.insert(6);
  List list2{list};
  ss << list2;
  CHECK(ss.str() == "5 6 7");

  SECTION("Copy change")
  {
    stringstream ss{};
    stringstream ss2{};
    List list{5, 6, 10};
    List list2{list};
    list2.insert(7);
    list2.remove(0);
    list.remove(0);
    ss << list;
    ss2 << list2;
    CHECK(ss.str() == "6 10");
    CHECK(ss2.str() == "6 7 10");
  }
}

TEST_CASE("Copy operator")
{
  sstringstream ss{};
  List list{5, 6, 10};
  List list2 = list;
  sslist << list2;
  CHECK(ss.str() == "5 6 10");
}

// move constructor
// move operator
// index operator
// iterator
// operator =
// operator ==
// operator !=
// operator *
// operator ++
// for loop
// fixa sublist och lägga till test för det