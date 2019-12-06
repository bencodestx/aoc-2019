#pragma once

#include <algorithm>
#include <bitset>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr int ROWS = 25'000;
constexpr int COLS = 25'000;
constexpr int NBITS = ROWS * COLS;
constexpr int ZERO_COL = COLS / 2;
constexpr int ZERO_ROW = ROWS / 2;

struct Location {
  int row{};
  int col{};

  void move(const char direction) {
    switch (direction) {
    case 'R':
      ++col;
      break;
    case 'L':
      --col;
      break;
    case 'U':
      --row;
      break;
    case 'D':
      ++row;
      break;
    default:
      throw std::runtime_error("Invalid direction");
    }
  };

  int toIndex() const { return (row + ZERO_ROW) * COLS + (col + ZERO_COL); }

  int manhattan_distance() const { return std::abs(row) + std::abs(col); }

  bool operator==(const Location &rhs) const {
    return row == rhs.row and col == rhs.col;
  }

  static Location fromIndex(int index) {
    const auto col = index % COLS - ZERO_COL;
    const auto row = index / COLS - ZERO_ROW;

    return {row, col};
  }
};

struct Matrix {
  Matrix() {}

  Matrix(const std::bitset<NBITS> &b) : bits(b) {}

  void mark(const Location l) { bits.set(l.toIndex()); }

  bool marked(const Location l) const { return bits.test(l.toIndex()); }

  void intersectWith(const Matrix &m) { bits &= m.bits; }

  std::vector<Location> markedLocations() const {
    std::vector<Location> results{};
    for (int index = 0; index < NBITS; ++index) {
      const auto l = Location::fromIndex(index);
      if (marked(l)) {
        results.push_back(l);
      }
    }
    return results;
  }

  std::bitset<NBITS> bits{};
};

std::unique_ptr<Matrix> load_matrix(const std::string &instructions) {
  auto m = std::make_unique<Matrix>();
  std::stringstream s{instructions};
  std::string instruction{};

  Location l{};
  while (std::getline(s, instruction, ',')) {
    const char direction = instruction[0];
    const int distance = std::stod(instruction.substr(1));
    for (int i = 0; i < distance; ++i) {
      l.move(direction);
      m->mark(l);
    }
  }

  return m;
}

std::vector<Location> intersections(const std::string &a,
                                    const std::string &b) {
  auto m = load_matrix(a);
  m->intersectWith(*load_matrix(b));
  return m->markedLocations();
}

std::vector<int> distances(const std::vector<Location> &intersections) {
  std::vector<int> result{};
  std::for_each(std::cbegin(intersections), std::cend(intersections),
                [&result](const auto intersection) {
                  result.push_back(intersection.manhattan_distance());
                });
  return result;
}

int day3_part1(const std::string &a, const std::string &b) {
  const auto results = distances(intersections(a, b));
  return *std::min_element(std::cbegin(results), std::cend(results));
}

template <size_t N>
void measure(const std::string &instructions,
             const std::vector<Location> &intersections,
             std::vector<std::array<int, 2>> &distances) {
  std::stringstream s{instructions};
  std::string instruction{};

  Location l{};
  int wire_distance = 0;
  while (std::getline(s, instruction, ',')) {
    const char direction = instruction[0];
    const int distance = std::stod(instruction.substr(1));
    for (int i = 0; i < distance; ++i) {
      l.move(direction);
      ++wire_distance;
      const auto it =
          std::find(std::cbegin(intersections), std::cend(intersections), l);
      if (it != std::cend(intersections)) {
        const auto index = std::distance(std::cbegin(intersections), it);
        if (0 == distances[index][N]) {
          distances[index][N] = wire_distance;
        }
      }
    }
  }
}

int day3_part2(const std::string &a, const std::string &b) {
  const auto ints = intersections(a, b);
  std::vector<std::array<int, 2>> distances{};
  distances.resize(ints.size());

  measure<0>(a, ints, distances);
  measure<1>(b, ints, distances);

  std::vector<int> sums{};
  std::for_each(std::cbegin(distances), std::cend(distances),
                [&sums](const auto distance) {
                  sums.push_back(distance[0] + distance[1]);
                });

  return *std::min_element(std::cbegin(sums), std::cend(sums));
}
