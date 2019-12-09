#pragma once

#include <algorithm>
#include <array>
#include <vector>

constexpr size_t IMAGE_SIZE = 25 * 6;

int day8_part1(const std::vector<char> &input) {
  int result = -1;
  int fewest_zeroes = IMAGE_SIZE + 1;
  for (size_t start = 0; start < input.size(); start += IMAGE_SIZE) {
    int zeroes = 0;
    int ones = 0;
    int twos = 0;
    for (size_t i = start; i < start + IMAGE_SIZE; ++i) {
      switch (input[i]) {
      case '0':
        ++zeroes;
        break;
      case '1':
        ++ones;
        break;
      case '2':
        ++twos;
        break;
      default:
        break;
      }
    }
    if (zeroes < fewest_zeroes) {
      fewest_zeroes = zeroes;
      result = ones * twos;
    }
  }
  return result;
}

std::array<char, IMAGE_SIZE> day8_part2(const std::vector<char> &input) {
  std::array<char, IMAGE_SIZE> image;
  std::fill(image.begin(), image.end(), '2');
  for (size_t position = 0; position < input.size(); ++position) {
    const size_t mod_position = position % IMAGE_SIZE;
    if ('2' == image[mod_position]) {
      image[mod_position] = input[position];
    }
  }
  return image;
}
