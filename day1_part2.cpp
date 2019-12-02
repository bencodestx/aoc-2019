#include <algorithm>
#include <iostream>

#include "day1_part2.hpp"
#include "input.hpp"

int main() {
  const auto masses = read<int64_t>();
  int64_t total{};

  std::for_each(std::cbegin(masses), std::cend(masses),
                [&total](const auto mass) { total += fuel_required(mass); });

  std::cout << total << std::endl;
}
