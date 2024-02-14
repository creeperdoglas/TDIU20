#include "catch.hpp"
#include <sstream>
#include "Time.h"

using namespace std;

TEST_CASE("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK(empty.get_hour() == 0);
      CHECK(empty.get_minute() == 0);
      CHECK(empty.get_second() == 0);
   }

   SECTION("Integer")
   {
      Time t0{0, 0, 0};
      Time t1{12, 30, 30};
      Time t2{23, 59, 59};

      CHECK_THROWS(Time{13, 35, 60});
      CHECK_THROWS(Time{13, 60, 35});
      CHECK_THROWS(Time{24, 35, 35});

      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS(Time{"13:35:60"});
      CHECK_THROWS(Time{"13:60:35"});
      CHECK_THROWS(Time{"24:35:35"});

      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);
   }
}

TEST_CASE("is_am")
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK(t0.is_am());
   CHECK_FALSE(t1.is_am());
   Time t2{"00:00:00"};
   CHECK(t2.is_am());
   Time t3{"12:00:00"};
   CHECK_FALSE(t3.is_am());
   Time t4("23:59:59");
   CHECK_FALSE(t4.is_am());
   Time t5("11:59:59");
   CHECK(t5.is_am());
}

TEST_CASE("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{5, 5, 5};
   // additonal tests
   SECTION("24 hour format no argument")
   {
      CHECK(t0.to_string() == "00:00:00");
      CHECK(t1.to_string() == "11:59:59");
      CHECK(t2.to_string() == "12:00:00");
      CHECK(t3.to_string() == "13:00:00");
      CHECK(t4.to_string() == "23:59:59");
      CHECK(t5.to_string() == "05:05:05");
   }

   SECTION("24 hour format with argument")
   {
      CHECK(t0.to_string(false) == "00:00:00");
      CHECK(t1.to_string(false) == "11:59:59");
      CHECK(t2.to_string(false) == "12:00:00");
      CHECK(t3.to_string(false) == "13:00:00");
      CHECK(t4.to_string(false) == "23:59:59");
      CHECK(t5.to_string(false) == "05:05:05");
   }

   SECTION("12 hour format")
   {
      CHECK(t0.to_string(true) == "12:00:00 AM");
      CHECK(t1.to_string(true) == "11:59:59 AM");
      CHECK(t2.to_string(true) == "12:00:00 PM");
      CHECK(t3.to_string(true) == "01:00:00 PM");
      CHECK(t4.to_string(true) == "11:59:59 PM");
      CHECK(t5.to_string(true) == "05:05:05 AM");
   }
}
TEST_CASE("Operator +")
{
   Time t1{11, 59, 59};
   CHECK((t1 + 1).to_string() == "12:00:00");
   CHECK((t1 + 129605).to_string() == "00:00:04");
   CHECK((t1 = t1 + 129605).to_string() == "00:00:04");
   // kommunativa fallet längre ned
}
TEST_CASE("Operator +=")
{
   Time t1{11, 59, 59};
   CHECK((t1 += 1).to_string() == "12:00:00");
   CHECK((t1 += 129605).to_string() == "00:00:05");
}
TEST_CASE("Operator ++")
{
   Time t0{0, 0, 0};
   Time t1{0, 1, 0};
   t1 = t0++;
   CHECK((t0).to_string() == "00:00:01");
   CHECK((t1).to_string() == "00:00:00");
}
TEST_CASE("++ operator")
{
   Time t0{0, 0, 0};
   Time t1{0, 1, 0};
   t1 = ++t0;
   CHECK((t0).to_string() == "00:00:01");
   CHECK((t1).to_string() == "00:00:01");
}

TEST_CASE("Operator - ")
{
   Time t1{11, 59, 59};
   CHECK((t1 - 1).to_string() == "11:59:58");
   CHECK((t1 - -1).to_string() == "12:00:00");
   CHECK((t1 = t1 - 129605).to_string() == "23:59:54");
}
TEST_CASE("Operator -= ")
{
   Time t1{12, 0, 1};
   CHECK((t1 -= 129605).to_string() == "23:59:56");
}
TEST_CASE("operator --")
{
   Time t0{0, 0, 0};
   Time t1{0, 1, 0};
   t1 = t0--;
   CHECK(t0.to_string() == "23:59:59");
   CHECK(t1.to_string() == "00:00:00");
}

TEST_CASE("-- operator")
{
   Time t0{0, 0, 0};
   Time t1{0, 1, 0};
   t1 = --t0;
   CHECK(t0.to_string() == "23:59:59");
   CHECK(t1.to_string() == "23:59:59");
}
TEST_CASE(" Boolean operators")
{
   SECTION("1")
   {
      Time t1{0, 0, 0};
      Time t2{23, 59, 59};
      Time t3 = t2;

      CHECK(t1 < t2);
      CHECK(t2 > t1);
      CHECK_FALSE(t2 > t3);
      CHECK_FALSE(t2 < t3);
      CHECK(t2 == t3);
      CHECK(t2 != t1);
      CHECK(t1 <= t2);
      CHECK(t2 >= t1);
      CHECK(t2 <= t3);
      CHECK(t2 >= t3);
   }

   SECTION("2")
   {
      Time t1{0, 0, 0};
      Time t2{0, 0, 2};
      Time t3 = t2;

      CHECK(t1 < t2);
      CHECK(t2 > t1);
      CHECK_FALSE(t2 > t3);
      CHECK_FALSE(t2 < t3);
      CHECK(t2 == t3);
      CHECK(t2 != t1);
      CHECK(t1 <= t2);
      CHECK(t2 >= t1);
      CHECK(t2 <= t3);
      CHECK(t2 >= t3);
   }

   SECTION("3")
   {
      Time t1{0, 0, 0};
      Time t2{0, 1, 0};
      Time t3 = t2;

      CHECK(t1 < t2);
      CHECK(t2 > t1);
      CHECK_FALSE(t2 > t3);
      CHECK_FALSE(t2 < t3);
      CHECK(t2 == t3);
      CHECK(t2 != t1);
      CHECK(t1 <= t2);
      CHECK(t2 >= t1);
      CHECK(t2 <= t3);
      CHECK(t2 >= t3);
   }

   SECTION("4")
   {
      Time t1{0, 0, 0};
      Time t2{1, 0, 0};
      Time t3 = t2;

      CHECK(t1 < t2);
      CHECK(t2 > t1);
      CHECK_FALSE(t2 > t3);
      CHECK_FALSE(t2 < t3);
      CHECK(t2 == t3);
      CHECK(t2 != t1);
      CHECK(t1 <= t2);
      CHECK(t2 >= t1);
      CHECK(t2 <= t3);
      CHECK(t2 >= t3);
   }
}

TEST_CASE("Output Stream Operator")
{

   stringstream ss;
   ss << Time{10, 20, 30};
   CHECK(ss.str() == "10:20:30");
}

TEST_CASE("Input Stream Operator")
{
   stringstream ss;
   Time t{};
   ss << "11:22:33";
   CHECK(ss.eof() == false);
   ss >> t;
   CHECK(t.to_string() == "11:22:33");
   CHECK(ss.eof());

   SECTION("Failbit")
   {
      stringstream ss("11:22:33");
      Time t2;
      ss >> t2;
      CHECK_FALSE(ss.fail());
      Time t3{};
      ss << "25:23:23";
      ss >> t3;
      CHECK(ss.fail());
   }
}

TEST_CASE("commutative")
{
   Time t1(10, 20, 30);
   CHECK((3600 + t1).to_string() == "11:20:30");
   CHECK((129605 + t1).to_string() == "22:20:35");
}