#include "day7.hpp"
#include "intcode.hpp"
#include <iostream>

int main() {
  const auto phase_combinations = list_combinations<5>({0, 1, 2, 3, 4});
  int best = 0;
  for (const auto &phase_combination : phase_combinations) {
    best = std::max(best, day7_part1(intcode::read(), phase_combination));
  }
  std::cout << best << std::endl;
}
