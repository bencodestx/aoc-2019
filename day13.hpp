#pragma once

#include <map>

#include "intcode.hpp"

namespace arcade {

struct Position {
  int x{};
  int y{};
};

using Board = std::map<int, std::map<int, int64_t>>;

std::tuple<int, int> play(intcode::Registers &registers) {
  Board b;
  Position p{};
  int mode{0};
  int64_t score{0};

  auto in_fn = [&]() -> int64_t {
    int ball{};
    int paddle{};

    for (const auto &row : b) {
      int col = 0;
      for (const auto &column : row.second) {
        while (col < column.first) {
          std::cout << ' ';
          ++col;
        }
        switch (column.second) {
        case 1:
          std::cout << '@';
          break;
        case 2:
          std::cout << '*';
          break;
        case 3:
          paddle = col;
          std::cout << '-';
          break;
        case 4:
          ball = col;
          std::cout << 'o';
          break;
        default:
          std::cout << ' ';
          break;
        }
        ++col;
      }
      std::cout << '\n';
    }
    std::cout << "\n   *** Score: " << score << " ***\n\n\n";

    if (ball == paddle) {
      return 0;
    } else if (ball < paddle) {
      return -1;
    } else {
      return 1;
    }
  };

  auto out_fn = [&](const int64_t x) {
    switch (mode) {
    case 0:
      p.x = x;
      break;
    case 1:
      p.y = x;
      break;
    case 2:
      if (p.x == -1 and p.y == 0) {
        score = x;
      } else {
        b[p.y][p.x] = x;
      }
      break;
    default:
      throw std::runtime_error("Bad mode");
    }
    mode = (mode + 1) % 3;
  };

  intcode::execute(registers, in_fn, out_fn);

  int blocks = 0;
  for (const auto &row : b) {
    for (const auto &column : row.second) {
      if (column.second == 2) {
        ++blocks;
      }
    }
  }
  return {blocks, score};
}

} // namespace arcade

int day13_part1(intcode::Registers &registers) {
  const auto [blocks, _] = arcade::play(registers);
  return blocks;
}

int day13_part2(intcode::Registers &registers) {
  registers[0] = 2;
  const auto [_, score] = arcade::play(registers);
  return score;
}
