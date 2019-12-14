#include <catch2/catch.hpp>

#include "intcode.hpp"

TEST_CASE("1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2)", "[day2]") {
  auto registers = intcode::from_vector({1, 0, 0, 0, 99});
  intcode::execute(registers);
  REQUIRE(registers == intcode::from_vector({2, 0, 0, 0, 99}));
}

TEST_CASE("2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6)", "[day2]") {
  auto registers = intcode::from_vector({2, 3, 0, 3, 99});
  intcode::execute(registers);
  REQUIRE(registers == intcode::from_vector({2, 3, 0, 6, 99}));
}

TEST_CASE("2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801)", "[day2]") {
  auto registers = intcode::from_vector({2, 4, 4, 5, 99, 0});
  intcode::execute(registers);
  REQUIRE(registers == intcode::from_vector({2, 4, 4, 5, 99, 9801}));
}

TEST_CASE("1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99", "[day2]") {
  auto registers = intcode::from_vector({1, 1, 1, 4, 99, 5, 6, 0, 99});
  intcode::execute(registers);
  REQUIRE(registers == intcode::from_vector({30, 1, 1, 4, 2, 5, 6, 0, 99}));
}

TEST_CASE("3500 for 9/10", "[day2]") {
  const auto sample_registers =
      intcode::from_vector({1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50});
  REQUIRE(3500 == intcode::execute(9, 10, sample_registers));
}

TEST_CASE("109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 takes no "
          "input and produces a copy of itself as output",
          "[day9]") {
  const std::vector<int64_t> initial{109,  1,   204, -1,  1001, 100, 1, 100,
                                     1008, 100, 16,  101, 1006, 101, 0, 99};
  std::vector<int64_t> outputs{};
  auto registers = intcode::from_vector(initial);
  intcode::execute(
      registers, []() { return 0; },
      [&outputs](const int64_t x) { outputs.push_back(x); });

  REQUIRE(initial == outputs);
}

TEST_CASE("1102,34915192,34915192,7,4,7,99,0 should output a 16-digit number",
          "[day9]") {
  auto registers =
      intcode::from_vector({1102, 34915192, 34915192, 7, 4, 7, 99, 0});
  std::vector<int64_t> outputs{};
  intcode::execute(
      registers, []() { return 0; },
      [&outputs](const int64_t x) { outputs.push_back(x); });

  REQUIRE(std::size(outputs) == 1);
  REQUIRE(outputs[0] >= 1000'0000'0000'0000);
  REQUIRE(outputs[0] < 2000'0000'0000'0000);
}

TEST_CASE(
    "104,1125899906842624,99 should output the large number in the middle",
    "[day9]") {
  auto registers = intcode::from_vector({104, 1125899906842624, 99});
  std::vector<int64_t> outputs{};
  intcode::execute(
      registers, []() { return 0; },
      [&outputs](const int64_t x) { outputs.push_back(x); });

  REQUIRE(std::size(outputs) == 1);
  REQUIRE(outputs[0] == 1125899906842624);
}
