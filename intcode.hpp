#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace intcode {

using Registers = std::unordered_map<int64_t, int64_t>;

Registers from_vector(const std::vector<int64_t> &initial) {
  Registers registers;
  for (size_t i = 0; i < std::size(initial); ++i) {
    registers[i] = initial[i];
  }
  return registers;
}

bool is_halted(const Registers &registers, int64_t position) {
  if (const auto it = registers.find(position); std::end(registers) != it) {
    return it->second == 99;
  }
  return false;
}

namespace detail {

constexpr auto default_input_int = []() {
  int64_t x;
  std::cin >> x;
  return x;
};

constexpr auto default_output_int = [](const int64_t i) {
  std::cout << i << std::endl;
};

template <typename InputFn, typename OutputFn>
int64_t execute(Registers &registers, int64_t &relative_offset,
                InputFn &&input_int, OutputFn &&output_int,
                const int64_t initial_position, const bool break_after_output) {
  size_t position = initial_position;
  std::array<int64_t, 3> immediates{0, 0, 0};
  std::array<int64_t *, 3> ptrs{};
  while (true) {
    const auto instruction = registers[position + 0];
    const auto opcode = instruction % 100;
    const std::array<int64_t, 3> modes = {
        instruction / 100 % 10,
        instruction / 1'000 % 10,
        instruction / 10'000 % 10,
    };

    int operands;
    switch (opcode) {
    case 1:
    case 2:
    case 7:
    case 8:
      operands = 3;
      break;
    case 3:
    case 4:
    case 9:
      operands = 1;
      break;
    case 5:
    case 6:
      operands = 2;
      break;
    default:
      operands = 0;
      break;
    }

    for (int i = 0; i < operands; ++i) {
      switch (modes[i]) {
      case 0:
        ptrs[i] = &registers[registers[position + 1 + i]];
        break;
      case 1:
        immediates[i] = registers[position + 1 + i];
        ptrs[i] = &immediates[i];
        break;
      case 2:
        ptrs[i] = &registers[registers[position + 1 + i] + relative_offset];
        break;
      default:
        throw std::runtime_error("Unknown addressing mode");
      }
    }

    switch (opcode) {
    case 1:
      *(ptrs[2]) = *(ptrs[0]) + *(ptrs[1]);
      position += 4;
      break;
    case 2:
      *(ptrs[2]) = *(ptrs[0]) * *(ptrs[1]);
      position += 4;
      break;
    case 3:
      *(ptrs[0]) = input_int();
      position += 2;
      break;
    case 4:
      output_int(*ptrs[0]);
      position += 2;
      if (break_after_output) {
        return position;
      }
      break;
    case 5:
      if (0 != *ptrs[0]) {
        position = *ptrs[1];
      } else {
        position += 3;
      }
      break;
    case 6:
      if (0 == *ptrs[0]) {
        position = *ptrs[1];
      } else {
        position += 3;
      }
      break;
    case 7:
      if (*ptrs[0] < *ptrs[1]) {
        *ptrs[2] = 1;
      } else {
        *ptrs[2] = 0;
      }
      position += 4;
      break;
    case 8:
      if (*ptrs[0] == *ptrs[1]) {
        *ptrs[2] = 1;
      } else {
        *ptrs[2] = 0;
      }
      position += 4;
      break;
    case 9:
      relative_offset += *ptrs[0];
      position += 2;
      break;
    case 99:
      return position;
    default:
      throw std::runtime_error("Invalid opcode");
    }
  }
}

} // namespace detail

void execute(Registers &registers, std::function<int64_t()> &&input_fn) {
  int64_t relative_offset{0};
  detail::execute(registers, relative_offset, input_fn,
                  detail::default_output_int, 0, false);
}

void execute(Registers &registers, std::function<int64_t()> &&input_fn,
             std::function<void(int64_t)> &&output_fn) {
  int64_t relative_offset{0};
  detail::execute(registers, relative_offset, input_fn, output_fn, 0, false);
}

void execute(Registers &registers) {
  int64_t relative_offset{0};
  detail::execute(registers, relative_offset, detail::default_input_int,
                  detail::default_output_int, 0, false);
}

void execute(const std::vector<int64_t> &initial) {
  auto registers = from_vector(initial);
  int64_t relative_offset{0};
  detail::execute(registers, relative_offset, detail::default_input_int,
                  detail::default_output_int, 0, false);
}

int64_t execute(Registers &registers, std::function<int()> &&input_fn,
                std::function<void(int)> &&output_fn,
                const int initial_position, const bool break_after_output) {
  int64_t relative_offset{0};
  return detail::execute(registers, relative_offset, input_fn, output_fn,
                         initial_position, break_after_output);
}

int64_t execute(const int64_t noun, const int64_t verb, Registers registers) {
  registers[1] = noun;
  registers[2] = verb;

  int64_t relative_offset{0};
  detail::execute(registers, relative_offset, detail::default_input_int,
                  detail::default_output_int, 0, false);

  return registers[0];
}

Registers read() {
  Registers registers;
  size_t position = 0;
  int64_t value;

  while (std::cin >> value) {
    char junk;
    std::cin >> junk;
    registers[position++] = value;
  }

  return registers;
}

} // namespace intcode
