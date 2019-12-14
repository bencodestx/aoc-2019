#include <iostream>

#include "day10.hpp"
#include "input.hpp"

int main() {
  const auto lines = read<std::string>();

  std::cout << day10_part2(lines) << std::endl;
}
