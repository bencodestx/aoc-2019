#include <catch2/catch.hpp>

#include "day6.hpp"

const std::vector<std::string> example = {"COM)B", "B)C", "C)D", "D)E",
                                          "E)F",   "B)G", "G)H", "D)I",
                                          "E)J",   "J)K", "K)L"};

TEST_CASE(
    "The total number of direct and indirect orbits in this example is 42",
    "[day6]") {
  REQUIRE(42 == day6_part1(example));
}
