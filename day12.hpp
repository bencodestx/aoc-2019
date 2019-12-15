#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>

namespace moon {
struct Moon {
  Moon(const std::string description) {
    std::string filtered{};
    for (const auto ch : description) {
      if (ch == ' ' or ch == '-' or std::isdigit(ch)) {
        filtered += ch;
      }
    }
    std::stringstream s{filtered};
    for (size_t i = 0; i < DIMENSIONS; ++i) {
      s >> pos[i];
      vel[i] = 0;
    }
  }

  static constexpr size_t DIMENSIONS = 3;

  static constexpr auto abssum = [](const int accum, const int x) {
    return accum + std::abs(x);
  };

  int potential_energy() const {
    return std::accumulate(std::cbegin(pos), std::cend(pos), 0, abssum);
  }

  int kinetic_energy() const {
    return std::accumulate(std::cbegin(vel), std::cend(vel), 0, abssum);
  }

  int total_energy() const { return potential_energy() * kinetic_energy(); }

  void move() {
    for (size_t i = 0; i < DIMENSIONS; ++i) {
      pos[i] += vel[i];
    }
  }

  void gravity(const Moon &other) {
    for (size_t i = 0; i < DIMENSIONS; ++i) {
      if (pos[i] < other.pos[i]) {
        vel[i]++;
      } else if (pos[i] > other.pos[i]) {
        vel[i]--;
      }
    }
  }

  std::array<int, DIMENSIONS> pos{};
  std::array<int, DIMENSIONS> vel{};
};
} // namespace moon

int day12_part1(const std::vector<std::string> &moon_descriptions) {
  using namespace moon;

  std::vector<Moon> moons{};
  for (const auto &description : moon_descriptions) {
    moons.push_back(Moon(description));
  }

  for (auto iteration = 0; iteration < 1000; ++iteration) {
    for (auto &m : moons) {
      for (const auto &other : moons) {
        m.gravity(other);
      }
    }
    for (auto &m : moons) {
      m.move();
    }
  }

  return std::accumulate(
      std::cbegin(moons), std::cend(moons), 0,
      [](const int accum, const Moon &m) { return accum + m.total_energy(); });
}

uint64_t day12_part2(const std::vector<std::string> &moon_descriptions) {
  using namespace moon;

  std::vector<Moon> moons{};
  for (const auto &description : moon_descriptions) {
    moons.push_back(Moon(description));
  }
  const auto initial_moons = moons;

  uint64_t iteration{0};
  size_t solved_dimensions = 0;
  std::array<uint64_t, 3> solutions{0, 0, 0};
  while (solved_dimensions < Moon::DIMENSIONS) {
    for (auto &m : moons) {
      for (const auto &other : moons) {
        m.gravity(other);
      }
    }
    for (auto &m : moons) {
      m.move();
    }
    ++iteration;
    for (size_t i = 0; i < Moon::DIMENSIONS; ++i) {
      if (0 < solutions[i]) {
        continue;
      }
      bool matches = true;
      for (size_t j = 0; matches and j < std::size(moons); ++j) {
        if (moons[j].pos[i] != initial_moons[j].pos[i]) {
          matches = false;
        } else if (moons[j].vel[i] != initial_moons[j].vel[i]) {
          matches = false;
        }
      }
      if (matches) {
        solutions[i] = iteration;
        ++solved_dimensions;
      }
    }
  }

  auto lcm = solutions;
  while (lcm[0] != lcm[1] or lcm[1] != lcm[2]) {
    if (lcm[1] < lcm[0]) {
      lcm[1] += solutions[1];
    } else if (lcm[2] < lcm[0]) {
      lcm[2] += solutions[2];
    } else {
      lcm[0] += solutions[0];
    }
  }
  return lcm[0];
}
