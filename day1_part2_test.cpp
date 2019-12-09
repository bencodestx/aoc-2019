#include <catch2/catch.hpp>

#include "day1.hpp"

TEST_CASE("A module of mass 14 still requires 2 fuel", "[day1]") {
  REQUIRE(2 == fuel_required_for_mass_and_fuel(14));
}

TEST_CASE("the total fuel required for a module of mass 1969 is 654 + 216 + 70 "
          "+ 21 + 5 = 966",
          "[day1]") {
  REQUIRE(966 == fuel_required_for_mass_and_fuel(1969));
}

TEST_CASE("The fuel required by a module of mass 100756 and its fuel is: 33583 "
          "+ 11192 + 3728 + 1240 + 411 + 135 + 43 + 12 + 2 = 50346",
          "[day1]") {
  REQUIRE(50346 == fuel_required_for_mass_and_fuel(100756));
}
