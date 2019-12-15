#include <iostream>

#include "day12.hpp"
#include "input.hpp"

int main() {
  auto moons = readlines();

  std::cout << day12_part1(moons) << std::endl;
}
