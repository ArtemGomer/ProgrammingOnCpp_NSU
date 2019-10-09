//
// Created by Gomer on 09.10.2019.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tritset.h"
TEST_CASE("Creating set"){
  tritset set1(5);
  REQUIRE(set1.Size() == 2);
  REQUIRE(set1.Capacity() == 5);
  tritset set2(0);
  REQUIRE(set2.Size() == 0);
  REQUIRE(set2.Capacity() == 0);
  REQUIRE_THROWS_AS(tritset(-2), std::invalid_argument);
}
TEST_CASE("Tritset operations"){
  SECTION("[]") {
    tritset set1(5);
    set1[1] = True;
    set1[2] = False;
    REQUIRE(Unknown == set1[0]);
    REQUIRE(True == set1[1]);
    REQUIRE(False == set1[2]);
    REQUIRE_THROWS_AS(set1[-1], std::invalid_argument);
    set1[10] = Unknown;
    REQUIRE(set1.Size() == 2);
    REQUIRE(set1.Capacity() == 5);
    set1[10] = True;
    REQUIRE(set1.Size() == 3);
    REQUIRE(set1.Capacity() == 11);
  }
  SECTION("Copy"){
    tritset set(10);
    tritset copy = set;
    REQUIRE(copy.Size() == 3);
    REQUIRE(copy.Capacity() == 10);
  }
  SECTION("|"){
    tritset set1(3);
    set1[0] = True;
    set1[1] = False;
    tritset set2(4);
    tritset set3 = set1 | set2;
    REQUIRE(set3[0] == True);
    REQUIRE(set3[1] == Unknown);
    REQUIRE(set3.Size() == 2);
    REQUIRE(set3.Capacity() == 4);
  }
  SECTION("&") {
    tritset set1(3);
    set1[0] = True;
    set1[1] = False;
    tritset set2(4);
    tritset set3 = set1 & set2;
    REQUIRE(set3[0] == Unknown);
    REQUIRE(set3[1] == False);
    REQUIRE(set3.Size() == 2);
    REQUIRE(set3.Capacity() == 4);
  }
  SECTION("~") {
    tritset set1(3);
    set1[0] = True;
    set1[1] = False;
    tritset set2 = ~set1;
    REQUIRE(set2[0] == False);
    REQUIRE(set2[1] == True);
    REQUIRE(set2[2] == Unknown);
    REQUIRE(set2.Size() == 1);
    REQUIRE(set2.Capacity() == 3);
  }
  SECTION("Shrink"){
    tritset set(10);
    set[5] = True;
    set.Shrink();
    REQUIRE(set.Size() == 2);
    REQUIRE(set.Capacity() == 6);
  }
  SECTION("Trim"){
    tritset set(5);
    set[3] = True;
    set[4] = False;
    set.Trim(3);
    REQUIRE(set[3] == Unknown);
    REQUIRE(set[4] == Unknown);
    REQUIRE(set.Size() == 2);
    REQUIRE(set.Capacity() == 5);
  }
  SECTION("Cardinality"){
    tritset set(4);
    set[0] = True;
    set[1] = True;
    set[2] = False;
    REQUIRE(set.Cardinality(True) == 2);
    REQUIRE(set.Cardinality(False) == 1);
    REQUIRE(set.Cardinality(Unknown) == 1);
  }
  SECTION("Logical_length"){
    tritset set(10);
    set[6] = True;
    REQUIRE(set.logicalLength() == 7);
  }
}
