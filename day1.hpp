#pragma once

#include <numeric>

constexpr auto fuel_required_for_mass = [](const auto mass) {
  return mass / 3 - 2;
};

constexpr int fuel_required_for_mass_and_fuel(const int mass) {
  const auto base = fuel_required_for_mass(mass);
  return (base > 0) ? base + fuel_required_for_mass_and_fuel(base) : 0;
}

constexpr auto day1 = [](const auto &masses, auto &&transform_fn) {
  return std::accumulate(std::cbegin(masses), std::cend(masses), 0,
                         [transform_fn](const auto current, const auto mass) {
                           return current + transform_fn(mass);
                         });
};

constexpr auto day1_part1 = [](const auto &masses) {
  return day1(masses, fuel_required_for_mass);
};

constexpr auto day1_part2 = [](const auto &masses) {
  return day1(masses, fuel_required_for_mass_and_fuel);
};
