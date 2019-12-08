#include "day6.hpp"
#include "input.hpp"

int main() {
  const auto orbits = read<std::string>();

  std::cout << day6_part1(orbits) << std::endl;
}
