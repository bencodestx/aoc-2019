#include <iostream>

#include "day4.hpp"

int main() {
  const auto x = input();
  std::cout << day4_part<2>(x.first, x.second) << std::endl;
}
