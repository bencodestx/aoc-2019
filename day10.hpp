#pragma once

#include <algorithm>
#include <unordered_set>
#include <vector>

#include "asteroids.hpp"

inline std::vector<asteroids::Point>
points(const std::vector<std::string> &lines) {
  std::vector<asteroids::Point> results{};
  double y = 0.0;
  for (const auto &line : lines) {
    double x = 0.0;
    for (const char c : line) {
      if (c == '#') {
        results.push_back({x, y});
      }
      x += 1.0;
    }
    y += 1.0;
  }
  return results;
}

inline std::tuple<size_t, asteroids::Point>
max_and_location(const std::vector<asteroids::Point> &all) {
  asteroids::Point best{};
  size_t maximum{0};
  for (const auto start : all) {
    std::unordered_set<int> directions{};
    for (const auto end : all) {
      if (start != end) {
        const auto direction = static_cast<int>(
            asteroids::direction_between_points(start, end) * 1'000'000);
        directions.insert(direction);
      }
    }
    if (std::size(directions) > maximum) {
      maximum = std::size(directions);
      best = start;
    }
  }
  return {maximum, best};
}

inline int day10_part1(const std::vector<std::string> &lines) {
  const auto all = points(lines);
  const auto [maximum, _] = max_and_location(all);
  return maximum;
}

inline int day10_part2(const std::vector<std::string> &lines,
                       int shot_limit = 200) {
  const auto all = points(lines);
  const auto [_, origin] = max_and_location(all);

  using Other = std::tuple<asteroids::Point, int, double, bool>;
  std::vector<Other> others{};
  for (const auto &other : all) {
    if (other != origin) {
      const auto direction = static_cast<int>(
          asteroids::direction_between_points(origin, other) * 1'000'000);
      const auto distance = asteroids::distance_between_points(origin, other);

      others.push_back({other, direction, distance, false});
    }
  }

  std::sort(std::begin(others), std::end(others),
            [](const auto &a, const auto &b) {
              return (std::get<int>(a) < std::get<int>(b)) or
                     ((std::get<int>(a) == std::get<int>(b)) and
                      (std::get<double>(a) < std::get<double>(b)));
            });

  size_t index = 0;
  int shots = 0;
  int last_shot = -1;
  bool reset_trigger = true;
  while (std::get<int>(others[index]) < 270'000'000) {
    ++index;
  }
  while (true) {
    auto &other = others[index];
    if (std::get<int>(other) != last_shot) {
      reset_trigger = true;
    }
    if (reset_trigger and not std::get<bool>(other)) {
      reset_trigger = false;
      last_shot = std::get<int>(other);
      std::get<bool>(other) = true;
      if (++shots == shot_limit) {
        const auto asteroid = std::get<asteroids::Point>(other);
        return asteroid.x * 100 + asteroid.y;
      }
    }
    index = (index + 1) % std::size(others);
  }
}
