//
// Created by Gomer on 09.10.2019.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tritset.h"
TEST_CASE("Creating set") {
  tritset set1(5);
  REQUIRE(set1.size() == 2);
  REQUIRE(set1.capacity() == 5);
  tritset set2(0);
  REQUIRE(set2.size() == 0);
  REQUIRE(set2.capacity() == 0);
  REQUIRE_THROWS_AS(tritset(-2), std::invalid_argument);
}
TEST_CASE("Tritset operations") {
  SECTION("[]") {
    tritset set1(5);
    set1[1] = trit::True;
    set1[2] = trit::False;
    REQUIRE(trit::Unknown == set1[0]);
    REQUIRE(trit::True == set1[1]);
    REQUIRE(trit::False == set1[2]);
    REQUIRE_THROWS_AS(set1[-1], std::invalid_argument);
    set1[10] = trit::Unknown;
    REQUIRE(set1.size() == 2);
    REQUIRE(set1.capacity() == 5);
    set1[10] = trit::True;
    REQUIRE(set1.size() == 3);
    REQUIRE(set1.capacity() == 11);
  }
  SECTION("Copy") {
    tritset set(10);
    set[0] = trit::True;
    set[1] = trit::False;
    tritset copy = set;
    REQUIRE(set[0] == trit::True);
    REQUIRE(set[1] == trit::False);
    REQUIRE(copy.size() == 3);
    REQUIRE(copy.capacity() == 10);
  }
  SECTION("|") {
    tritset set1(3);
    set1[0] = trit::True;
    set1[1] = trit::False;
    tritset set2(4);
    tritset set3 = set1 | set2;
    REQUIRE(set3[0] == trit::True);
    REQUIRE(set3[1] == trit::Unknown);
    REQUIRE(set3.size() == 2);
    REQUIRE(set3.capacity() == 4);
  }
  SECTION("&") {
    tritset set1(3);
    set1[0] = trit::True;
    set1[1] = trit::False;
    tritset set2(4);
    tritset set3 = set1 & set2;
    REQUIRE(set3[0] == trit::Unknown);
    REQUIRE(set3[1] == trit::False);
    REQUIRE(set3.size() == 2);
    REQUIRE(set3.capacity() == 4);
  }
  SECTION("~") {
    tritset set1(3);
    set1[0] = trit::True;
    set1[1] = trit::False;
    tritset set2 = ~set1;
    REQUIRE(set2[0] == trit::False);
    REQUIRE(set2[1] == trit::True);
    REQUIRE(set2[2] == trit::Unknown);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.capacity() == 3);
  }
  SECTION("Shrink") {
    tritset set(10);
    set[5] = trit::True;
    set.shrink();
    REQUIRE(set.size() == 2);
    REQUIRE(set.capacity() == 6);
    tritset set0(10);
    set0.shrink();
    REQUIRE(set0.logicalLength() == 0);
    REQUIRE(set0.size() == 0);
    REQUIRE(set0.capacity() == 0);
  }
  SECTION("Trim") {
    tritset set(5);
    set[3] = trit::True;
    set[4] = trit::False;
    set.trim(3);
    REQUIRE(set[3] == trit::Unknown);
    REQUIRE(set[4] == trit::Unknown);
    REQUIRE(set.size() == 2);
    REQUIRE(set.capacity() == 5);
  }
  SECTION("Cardinality") {
    tritset set(4);
    set[0] = trit::True;
    set[1] = trit::True;
    set[2] = trit::False;
    REQUIRE(set.cardinality(trit::True) == 2);
    REQUIRE(set.cardinality(trit::False) == 1);
    REQUIRE(set.cardinality(trit::Unknown) == 1);
    std::map<trit, size_t> stat = set.cardinality();
    REQUIRE(stat[trit::True] == 2);
    REQUIRE(stat[trit::False] == 1);
    REQUIRE(stat[trit::Unknown] == 1);
  }
  SECTION("Logical_length") {
    tritset set(10);
    set[6] = trit::True;
    REQUIRE(set.logicalLength() == 7);
  }
}
