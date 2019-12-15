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

std::vector<std::string> readlines() {
  std::vector<std::string> lines{};
  std::string line{};
  while (std::getline(std::cin, line)) {
    lines.push_back(line);
  }
  return lines;
}
