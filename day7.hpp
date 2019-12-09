#pragma once

#include "intcode.hpp"
#include <vector>

template <size_t N>
std::vector<std::array<int, N>>
list_combinations(const std::array<int, N> &options) {
  std::vector<std::array<int, N>> result;
  for (size_t i = 0; i < N; ++i) {
    const auto first = options[i];
    std::array<int, N - 1> rest{};
    for (size_t j = 0; j < i; ++j) {
      rest[j] = options[j];
    }
    for (size_t j = i + 1; j < N; ++j) {
      rest[j - 1] = options[j];
    }
    const auto others = list_combinations<N - 1>(rest);
    std::array<int, N> current = {first};
    for (const auto &other : others) {
      std::copy(other.begin(), other.end(), current.begin() + 1);
      result.push_back(current);
    }
  }
  return result;
}

template <>
std::vector<std::array<int, 1>>
list_combinations(const std::array<int, 1> &options) {
  return {options};
}

int amplify(intcode::Registers registers, const int phase, const int input) {
  bool first_call = true;
  auto on_input = [&first_call, phase, input]() {
    if (first_call) {
      first_call = false;
      return phase;
    } else {
      return input;
    }
  };

  int output = -1;
  auto on_output = [&output](const int x) { output = x; };

  intcode::execute(registers, on_input, on_output);

  return output;
}

int day7_part1(const intcode::Registers &program,
               const std::array<int, 5> &phases) {
  int input = 0;
  for (size_t i = 0; i < phases.size(); ++i) {
    input = amplify(program, phases[i], input);
  }
  return input;
}

int day7_part2(const intcode::Registers &init,
               const std::array<int, 5> &phases) {
  std::array<intcode::Registers, 5> r = {init, init, init, init, init};
  std::array<int, 5> ip = {0, 0, 0, 0, 0};
  std::array<bool, 5> has_read_phase = {false, false, false, false, false};

  int next_input = 0;
  while (not intcode::is_halted(r[4], ip[4])) {
    for (int i = 0; i < 5; ++i) {
      ip[i] = intcode::execute(
          r[i],
          [&]() {
            if (has_read_phase[i]) {
              return next_input;
            } else {
              has_read_phase[i] = true;
              return phases[i];
            }
          },
          [&next_input](const int x) { next_input = x; }, ip[i], true);
    }
  }

  return next_input;
}
