#include "day7.hpp"
#include "intcode.hpp"
#include <iostream>

int main() {
  const auto phase_combinations = list_combinations<5>({5, 6, 7, 8, 9});
  int best = 0;
  for (const auto &phase_combination : phase_combinations) {
    best = std::max(best, day7_part2(intcode::read(), phase_combination));
  }
  std::cout << best << std::endl;
}
