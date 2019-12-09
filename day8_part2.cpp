#include "day8.hpp"
#include "input.hpp"
#include <iostream>

int main() {
  const auto in = read<char>();
  const auto image = day8_part2(in);
  for (size_t i = 0; i < image.size(); ++i) {
    if ('1' == image[i]) {
      std::cout << '*';
    } else {
      std::cout << ' ';
    }
    if ((i + 1) % 25 == 0) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}
