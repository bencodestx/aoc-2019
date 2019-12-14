#include <catch2/catch.hpp>

#include "day10.hpp"

const std::vector<std::string> lines = {
    ".#..##.###...#######", "##.############..##.", ".#.######.########.#",
    ".###.#######.####.#.", "#####.##.#.##.###.##", "..#####..#.#########",
    "####################", "#.####....###.#.#.##", "##.#################",
    "#####.##.###..####..", "..######..##.#######", "####.##.####...##..#",
    ".#####..#.######.###", "##...#.##########...", "#.##########.#######",
    ".####.#.###.###.#.##", "....##.##.###..#####", ".#.#.###########.###",
    "#.#.#.#####.####.###", "###.##.####.##.#..##"};

TEST_CASE("The 1st asteroid to be vaporized is at 11,12", "[day10]") {
  REQUIRE(1112 == day10_part2(lines, 1));
}

TEST_CASE("The 2nd asteroid to be vaporized is at 12,1", "[day10]") {
  REQUIRE(1201 == day10_part2(lines, 2));
}

TEST_CASE("The 3rd asteroid to be vaporized is at 12,2", "[day10]") {
  REQUIRE(1202 == day10_part2(lines, 3));
}

TEST_CASE("The 10th asteroid to be vaporized is at 12,8", "[day10]") {
  REQUIRE(1208 == day10_part2(lines, 10));
}

TEST_CASE("The 20th asteroid to be vaporized is at 16,0", "[day10]") {
  REQUIRE(1600 == day10_part2(lines, 20));
}

TEST_CASE("The 50th asteroid to be vaporized is at 16,9", "[day10]") {
  REQUIRE(1609 == day10_part2(lines, 50));
}

TEST_CASE("The 100th asteroid to be vaporized is at 10,16", "[day10]") {
  REQUIRE(1016 == day10_part2(lines, 100));
}

TEST_CASE("The 199th asteroid to be vaporized is at 9,6", "[day10]") {
  REQUIRE(906 == day10_part2(lines, 199));
}

TEST_CASE("The 200th asteroid to be vaporized is at 8,2", "[day10]") {
  REQUIRE(802 == day10_part2(lines, 200));
  REQUIRE(802 == day10_part2(lines));
}

TEST_CASE("The 201st asteroid to be vaporized is at 10,9", "[day10]") {
  REQUIRE(1009 == day10_part2(lines, 201));
}

TEST_CASE("The 299th and final asteroid to be vaporized is at 11,1",
          "[day10]") {
  REQUIRE(1101 == day10_part2(lines, 299));
}
