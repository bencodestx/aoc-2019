#include <catch2/catch.hpp>

#include "day1_part1.hpp"

TEST_CASE("A module of mass 14 requires 2 fuel", "[day1]") {
  REQUIRE(2 == fuel_required(14));
}

TEST_CASE("For a mass of 1969, the fuel required is 654", "[day1]") {
  REQUIRE(654 == fuel_required(1969));
}

TEST_CASE("For a mass of 100756, the fuel required is 33583", "[day1]") {
  REQUIRE(33583 == fuel_required(100756));
}
