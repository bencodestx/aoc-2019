#include <iostream>

#include "day12.hpp"
#include "input.hpp"

int main() {
  auto moons = readlines();

  std::cout << day12_part2(moons) << std::endl;
}
