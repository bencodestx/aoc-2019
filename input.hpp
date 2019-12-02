#pragma once

#include <iostream>
#include <vector>

template <typename T> std::vector<T> read() {
  std::vector<T> values{};
  T value{};
  while (std::cin >> value) {
    values.push_back(value);
  }
  return values;
};
