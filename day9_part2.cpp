#include "day9.hpp"
#include <iostream>

int main() {
  auto registers = intcode::read();
  day9_part2(registers);
}
