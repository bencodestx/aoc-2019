#pragma once

#include <algorithm>
#include <array>
#include <string>

std::pair<int, int> input() {
  std::string in{};
  std::cin >> in;
  return {std::stod(in.substr(0, 6)), std::stod(in.substr(7))};
}

std::array<int, 6> digits(int number) {
  std::array<int, 6> digits;
  for (size_t index = 6; index > 0; --index) {
    digits[index - 1] = number % 10;
    number /= 10;
  }
  return digits;
}

auto two_digits_the_same = [](const auto digits) {
  for (size_t i = 0; i < (digits.size() - 1); ++i) {
    if (digits[i] == digits[i + 1]) {
      return true;
    }
  }
  return false;
};

auto two_digits_the_same_in_two_digit_set = [](const auto digits) {
  for (size_t i = 0; i < (digits.size() - 1); ++i) {
    if ((digits[i] == digits[i + 1]) and
        (i == 4 or (digits[i] != digits[i + 2])) and
        (i == 0 or (digits[i] != digits[i - 1]))) {
      return true;
    }
  }
  return false;
};

auto digits_do_not_decrease = [](const auto digits) {
  for (size_t i = 1; i < digits.size(); ++i) {
    if (digits[i - 1] > digits[i]) {
      return false;
    }
  }
  return true;
};

template <size_t part> int day4_part(int low, int high) {
  int valid{0};
  for (int candidate = low; candidate <= high; ++candidate) {
    const auto x = digits(candidate);
    if constexpr (part == 1) {
      if (not two_digits_the_same(x)) {
        continue;
      }
    } else if constexpr (part == 2) {
      if (not two_digits_the_same_in_two_digit_set(x)) {
        continue;
      }
    } else {
      static_assert(part == 1 or part == 2);
    }
    if (not digits_do_not_decrease(x)) {
      continue;
    }
    ++valid;
  }
  return valid;
}
