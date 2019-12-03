#include <catch2/catch.hpp>

#include "intcode.hpp"

TEST_CASE("1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2)", "[day2]") {
  intcode::Registers registers{1, 0, 0, 0, 99};
  intcode::execute(registers);
  REQUIRE(registers == intcode::Registers{2, 0, 0, 0, 99});
}

TEST_CASE("2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6)", "[day2]") {
  intcode::Registers registers{2, 3, 0, 3, 99};
  intcode::execute(registers);
  REQUIRE(registers == intcode::Registers{2, 3, 0, 6, 99});
}

TEST_CASE("2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801)", "[day2]") {
  intcode::Registers registers{2, 4, 4, 5, 99, 0};
  intcode::execute(registers);
  REQUIRE(registers == intcode::Registers{2, 4, 4, 5, 99, 9801});
}

TEST_CASE("1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99", "[day2]") {
  intcode::Registers registers{1, 1, 1, 4, 99, 5, 6, 0, 99};
  intcode::execute(registers);
  REQUIRE(registers == intcode::Registers{30, 1, 1, 4, 2, 5, 6, 0, 99});
}

TEST_CASE("3500 for 9/10", "[day2]") {
  const intcode::Registers sample_registers = {1,  9, 10, 3,  2,  3,
                                               11, 0, 99, 30, 40, 50};
  REQUIRE(3500 == intcode::execute(9, 10, sample_registers));
}
