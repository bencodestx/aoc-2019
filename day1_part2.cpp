#include <algorithm>
#include <iostream>

#include "input.hpp"

constexpr int64_t fuel_required(const int64_t mass) {
  const int64_t fuel_required_for_mass = mass / 3 - 2;
  if (fuel_required_for_mass > 0) {
    return fuel_required_for_mass + fuel_required(fuel_required_for_mass);
  } else {
    return 0;
  }
}

int main() {
  const auto masses = read<int64_t>();
  int64_t total{};

  std::for_each(std::cbegin(masses), std::cend(masses),
                [&total](const auto mass) { total += fuel_required(mass); });

  std::cout << total << std::endl;
}
