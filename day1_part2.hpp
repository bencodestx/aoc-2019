#pragma once

constexpr int64_t fuel_required(const int64_t mass) {
  const int64_t fuel_required_for_mass = mass / 3 - 2;
  if (fuel_required_for_mass > 0) {
    return fuel_required_for_mass + fuel_required(fuel_required_for_mass);
  } else {
    return 0;
  }
}
