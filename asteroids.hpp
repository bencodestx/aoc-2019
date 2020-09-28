#pragma once

#include <cmath>

namespace asteroids {

constexpr double close(const double a, const double b) {
  constexpr double EPSILON = 0.000'000'1;
  return std::abs(a - b) <= EPSILON;
}

struct Point {
  double x{};
  double y{};

  bool operator==(const Point &b) const {
    return close(x, b.x) and close(y, b.y);
  }

  bool operator!=(const Point &b) const {
    return not close(x, b.x) or not close(y, b.y);
  }
};

constexpr double rad_to_deg(const double radians) {
  constexpr double half_c = 180 / M_PI;
  return radians * half_c;
}

inline double degrees(const Point p) {
  return rad_to_deg(std::atan(std::abs(p.y) / std::abs(p.x)));
}

enum class Quadrant { I, II, III, IV };

constexpr Quadrant quadrant(const Point p) {
  if (p.x >= 0) {
    if (p.y >= 0) {
      return Quadrant::I;
    } else {
      return Quadrant::IV;
    }
  } else if (p.y >= 0) {
    return Quadrant::II;
  } else {
    return Quadrant::III;
  }
}

inline double direction_between_points(const Point a, const Point b) {
  const Point delta{b.x - a.x, b.y - a.y};

  const auto q = quadrant(delta);

  if (close(delta.x, 0.0)) {
    switch (q) {
    case Quadrant::I:
    case Quadrant::II:
      return 90.0;
    case Quadrant::III:
    case Quadrant::IV:
      return 270.0;
    }
  }

  const auto angle = degrees(delta);
  switch (q) {
  case Quadrant::I:
    return angle;
    break;
  case Quadrant::II:
    return 180.0 - angle;
    break;
  case Quadrant::III:
    return 180.0 + angle;
    break;
  case Quadrant::IV:
    return 360.0 - angle;
    break;
  }

  return 0.0;
}

inline double distance_between_points(const Point a, const Point b) {
  const auto x = a.x - b.x;
  const auto y = a.y - b.y;
  return std::sqrt(x * x + y * y);
}

} // namespace asteroids
