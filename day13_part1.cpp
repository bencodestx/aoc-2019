#include <iostream>

#include "day13.hpp"
#include "intcode.hpp"

int main() {
  auto registers = intcode::read();

  std::cout << day13_part1(registers) << std::endl;
}
