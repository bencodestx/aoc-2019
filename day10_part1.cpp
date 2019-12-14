#include <iostream>

#include "day10.hpp"
#include "input.hpp"

int main() {
  const auto lines = read<std::string>();

  std::cout << day10_part1(lines) << std::endl;
}
