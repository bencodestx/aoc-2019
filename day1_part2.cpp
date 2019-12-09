#include <iostream>

#include "day1.hpp"
#include "input.hpp"

int main() {
  auto masses = read<int>();

  std::cout << day1_part2(masses) << std::endl;
}
