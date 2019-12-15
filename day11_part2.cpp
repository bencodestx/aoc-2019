#include <iostream>

#include "day11.hpp"
#include "intcode.hpp"

int main() {
  auto registers = intcode::read();

  std::cout << day11_part2(registers) << std::endl;
}
