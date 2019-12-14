#include <catch2/catch.hpp>

#include "day10.hpp"

TEST_CASE("The best location for a new monitoring station on this map is the "
          "highlighted asteroid at 3,4 because it can detect 8 asteroids",
          "[day10]") {
  std::vector<std::string> lines = {".#..#", ".....", "#####", "....#",
                                    "...##"};
  REQUIRE(8 == day10_part1(lines));
}

TEST_CASE("Best is 5,8 with 33 other asteroids detected", "[day10]") {
  std::vector<std::string> lines = {
      "......#.#.", "#..#.#....", "..#######.", ".#.#.###..", ".#..#.....",
      "..#....#.#", "#..#....#.", ".##.#..###", "##...#..#.", ".#....####"};
  REQUIRE(33 == day10_part1(lines));
}

TEST_CASE("Best is 1,2 with 35 other asteroids detected", "[day10]") {
  std::vector<std::string> lines = {
      "#.#...#.#.", ".###....#.", ".#....#...", "##.#.#.#.#", "....#.#.#.",
      ".##..###.#", "..#...##..", "..##....##", "......#...", ".####.###."};
  REQUIRE(35 == day10_part1(lines));
}

TEST_CASE("Best is 6,3 with 41 other asteroids detected", "[day10]") {
  std::vector<std::string> lines = {
      ".#..#..###", "####.###.#", "....###.#.", "..###.##.#", "##.##.#.#.",
      "....###..#", "..#.#..#.#", "#..#.#.###", ".##...##.#", ".....#.#.."};
  REQUIRE(41 == day10_part1(lines));
}

TEST_CASE("Best is 11,13 with 210 other asteroids detected", "[day10]") {
  std::vector<std::string> lines = {
      ".#..##.###...#######", "##.############..##.", ".#.######.########.#",
      ".###.#######.####.#.", "#####.##.#.##.###.##", "..#####..#.#########",
      "####################", "#.####....###.#.#.##", "##.#################",
      "#####.##.###..####..", "..######..##.#######", "####.##.####...##..#",
      ".#####..#.######.###", "##...#.##########...", "#.##########.#######",
      ".####.#.###.###.#.##", "....##.##.###..#####", ".#.#.###########.###",
      "#.#.#.#####.####.###", "###.##.####.##.#..##"};
  REQUIRE(210 == day10_part1(lines));
}
