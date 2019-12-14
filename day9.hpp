#pragma once

#include "intcode.hpp"

void day9_part1(intcode::Registers &registers) {
  intcode::execute(registers, []() { return 1; });
}

void day9_part2(intcode::Registers &registers) {
  intcode::execute(registers, []() { return 2; });
}
