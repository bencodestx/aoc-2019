#include <algorithm>
#include <iostream>

#include "input.hpp"

constexpr auto fuel_required = [](const uint64_t mass) { return mass / 3 - 2; };

int main() {
  const auto masses = read<uint64_t>();
  uint64_t total{};

  std::for_each(std::cbegin(masses), std::cend(masses),
                [&total](const auto mass) { total += fuel_required(mass); });

  std::cout << total << std::endl;
}
