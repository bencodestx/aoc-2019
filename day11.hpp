#pragma once

#include <unordered_map>

#include "intcode.hpp"

namespace paint {

enum class Direction { Up, Right, Down, Left };

Direction turn(const Direction d, const int64_t x) {
  if (x == 0) {
    switch (d) {
    case Direction::Up:
      return Direction::Left;
    case Direction::Left:
      return Direction::Down;
    case Direction::Down:
      return Direction::Right;
    case Direction::Right:
      return Direction::Up;
    }
  } else {
    switch (d) {
    case Direction::Up:
      return Direction::Right;
    case Direction::Right:
      return Direction::Down;
    case Direction::Down:
      return Direction::Left;
    case Direction::Left:
      return Direction::Up;
    }
  }
  throw std::runtime_error("Bad direction");
}

struct Position {
  using Key = uint64_t;
  uint64_t x{1'000'000};
  uint64_t y{1'000'000};

  Key key() const { return (x << 32) | y; }
};

Position move(const Position p, const Direction d) {
  switch (d) {
  case Direction::Up:
    return {p.x, p.y - 1};
  case Direction::Right:
    return {p.x + 1, p.y};
  case Direction::Down:
    return {p.x, p.y + 1};
  case Direction::Left:
    return {p.x - 1, p.y};
  }
  throw std::runtime_error("Bad move");
}

using Figure = std::unordered_map<Position::Key, int64_t>;

} // namespace paint

int day11_part1(intcode::Registers &registers) {
  using namespace paint;

  Figure f;
  Position p{};
  Direction d{Direction::Up};
  bool expecting_color = true;

  auto in_fn = [&p, &f]() -> int64_t {
    if (const auto it = f.find(p.key()); std::end(f) != it) {
      return it->second;
    }
    return 0;
  };

  auto out_fn = [&d, &p, &f, &expecting_color](const int64_t x) {
    if (expecting_color) {
      f[p.key()] = x;
    } else {
      d = turn(d, x);
      p = move(p, d);
    }
    expecting_color = not expecting_color;
  };

  intcode::execute(registers, in_fn, out_fn);

  return std::size(f);
}

std::string day11_part2(intcode::Registers &registers) {
  using namespace paint;

  Figure f;
  Position p{};
  Direction d{Direction::Up};
  bool expecting_color = true;
  uint64_t minx{p.x};
  uint64_t maxx{p.x};
  uint64_t miny{p.y};
  uint64_t maxy{p.y};

  f[p.key()] = 1;

  auto read = [&](const Position readpos) -> int64_t {
    if (const auto it = f.find(readpos.key()); std::end(f) != it) {
      return it->second;
    }
    return 0;
  };

  auto in_fn = [&]() { return read(p); };

  auto out_fn = [&](const int64_t x) {
    if (expecting_color) {
      f[p.key()] = x;
      miny = std::min(miny, p.y);
      maxy = std::max(maxy, p.y);
      minx = std::min(minx, p.x);
      maxx = std::max(maxx, p.x);
    } else {
      d = turn(d, x);
      p = move(p, d);
    }
    expecting_color = not expecting_color;
  };

  intcode::execute(registers, in_fn, out_fn);

  std::string image{};
  for (auto y = miny; y <= maxy; ++y) {
    for (auto x = minx; x <= maxx; ++x) {
      image += (read({x, y}) > 0) ? '*' : ' ';
    }
    image += '\n';
  }

  return image;
}
