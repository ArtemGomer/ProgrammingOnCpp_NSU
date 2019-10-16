//
// Created by Gomer on 09.10.2019.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tritset.h"
TEST_CASE("Creating set") {
  tritset set1(5);
  REQUIRE(set1.Size() == 2);
  REQUIRE(set1.Capacity() == 5);
  tritset set2(0);
  REQUIRE(set2.Size() == 0);
  REQUIRE(set2.Capacity() == 0);
  REQUIRE_THROWS_AS(tritset(-2), std::invalid_argument);
}
TEST_CASE("Tritset operations") {
  SECTION("[]") {
    tritset set1(5);
    set1[1] = TritValue::True;
    set1[2] = TritValue::False;
    REQUIRE(TritValue::Unknown == set1[0]);
    REQUIRE(TritValue::True == set1[1]);
    REQUIRE(TritValue::False == set1[2]);
    REQUIRE_THROWS_AS(set1[-1], std::invalid_argument);
    set1[10] = TritValue::Unknown;
    REQUIRE(set1.Size() == 2);
    REQUIRE(set1.Capacity() == 5);
    set1[10] = TritValue::True;
    REQUIRE(set1.Size() == 3);
    REQUIRE(set1.Capacity() == 11);
  }
  SECTION("Copy") {
    tritset set(10);
    set[0] = TritValue::True;
    set[1] = TritValue::False;
    tritset copy = set;
    REQUIRE(set[0] == TritValue::True);
    REQUIRE(set[1] == TritValue::False);
    REQUIRE(copy.Size() == 3);
    REQUIRE(copy.Capacity() == 10);
  }
  SECTION("|") {
    tritset set1(3);
    set1[0] = TritValue::True;
    set1[1] = TritValue::False;
    tritset set2(4);
    tritset set3 = set1 | set2;
    REQUIRE(set3[0] == TritValue::True);
    REQUIRE(set3[1] == TritValue::Unknown);
    REQUIRE(set3.Size() == 2);
    REQUIRE(set3.Capacity() == 4);
  }
  SECTION("&") {
    tritset set1(3);
    set1[0] = TritValue::True;
    set1[1] = TritValue::False;
    tritset set2(4);
    tritset set3 = set1 & set2;
    REQUIRE(set3[0] == TritValue::Unknown);
    REQUIRE(set3[1] == TritValue::False);
    REQUIRE(set3.Size() == 2);
    REQUIRE(set3.Capacity() == 4);
  }
  SECTION("~") {
    tritset set1(3);
    set1[0] = TritValue::True;
    set1[1] = TritValue::False;
    tritset set2 = ~set1;
    REQUIRE(set2[0] == TritValue::False);
    REQUIRE(set2[1] == TritValue::True);
    REQUIRE(set2[2] == TritValue::Unknown);
    REQUIRE(set2.Size() == 1);
    REQUIRE(set2.Capacity() == 3);
  }
  SECTION("Shrink") {
    tritset set(10);
    set[5] = TritValue::True;
    set.Shrink();
    REQUIRE(set.Size() == 2);
    REQUIRE(set.Capacity() == 6);
  }
  SECTION("Trim") {
    tritset set(5);
    set[3] = TritValue::True;
    set[4] = TritValue::False;
    set.Trim(3);
    REQUIRE(set[3] == TritValue::Unknown);
    REQUIRE(set[4] == TritValue::Unknown);
    REQUIRE(set.Size() == 2);
    REQUIRE(set.Capacity() == 5);
  }
  SECTION("Cardinality") {
    tritset set(4);
    set[0] = TritValue::True;
    set[1] = TritValue::True;
    set[2] = TritValue::False;
    REQUIRE(set.Cardinality(TritValue::True) == 2);
    REQUIRE(set.Cardinality(TritValue::False) == 1);
    REQUIRE(set.Cardinality(TritValue::Unknown) == 1);
    std::map<TritValue, int> stat = set.Cardinality();
    REQUIRE(stat[TritValue::True] == 2);
    REQUIRE(stat[TritValue::False] == 1);
    REQUIRE(stat[TritValue::Unknown] == 1);
  }
  SECTION("Logical_length") {
    tritset set(10);
    set[6] = TritValue::True;
    REQUIRE(set.logicalLength() == 7);
  }
}
