#pragma once

#include <string>
#include <unordered_map>
#include <vector>

int count_orbits(const std::string& orbiter, const std::unordered_map<std::string, std::string>& orbiter_to_orbitee) {
  static const std::string COM{"COM"};
  if (orbiter == COM) {
    return 0;
  } else {
    const auto it = orbiter_to_orbitee.find(orbiter);
    return 1 + count_orbits(it->second, orbiter_to_orbitee);
  }
}

int day6_part1(const std::vector<std::string>& orbits) {
  std::unordered_map<std::string, std::string> orbiter_to_orbitee{};
  for (const auto& orbit: orbits) {
    const auto split = orbit.find(')');
    orbiter_to_orbitee[orbit.substr(split+1)] = orbit.substr(0, split);
  }
  int orbit_count{};
  for (const auto& orbit: orbiter_to_orbitee) {
    orbit_count += 1 + count_orbits(orbit.second, orbiter_to_orbitee);
  }
  return orbit_count;
}

int day6_part2(const std::vector<std::string>& orbits) {
  std::unordered_map<std::string, std::string> orbiter_to_orbitee{};
  for (const auto& orbit: orbits) {
    const auto split = orbit.find(')');
    orbiter_to_orbitee[orbit.substr(split+1)] = orbit.substr(0, split);
  }
  const std::string first{"YOU"};
  const std::string second{"SAN"};
  const std::string COM{"COM"};
  std::unordered_map<std::string, std::pair<int, int>> distances{};
  auto location = orbiter_to_orbitee[first];
  int distance = 0;
  while (location != COM) {
    distances[location].first = distance++;
    distances[location].second = -1;
    location = orbiter_to_orbitee[location];
  }
  location = orbiter_to_orbitee[second];
  distance = 0;
  while (location != COM) {
    auto it = distances.find(location);
    if (distances.end() != it) {
      it->second.second = distance++;
    } else {
      distance++;
    }
    location = orbiter_to_orbitee[location];
  }
  int minimum_required_transfers = -1;
  for (const auto& distance: distances) {
    if (distance.second.second != -1) {
      const auto required_transfers = distance.second.first + distance.second.second;
      if (minimum_required_transfers == -1) { 
        minimum_required_transfers = required_transfers;
      } else {
        minimum_required_transfers = std::min(minimum_required_transfers, required_transfers);
      }
    }
  }
  return minimum_required_transfers;
}
