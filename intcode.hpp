#include <array>
#include <functional>
#include <iostream>

namespace intcode {

constexpr size_t REGISTER_COUNT = 1000;
using Registers = std::array<int, REGISTER_COUNT>;

void execute(
    Registers &registers,
    std::function<int()> &&input_int =
        []() {
          int x;
          std::cin >> x;
        },
    std::function<void(int)> &&output_int =
        [](const int i) { std::cout << i << std::endl; }) {
  size_t position = 0;
  std::array<int, 3> immediates{0, 0, 0};
  std::array<int *, 3> ptrs{};
  while (true) {
    const auto instruction = registers[position + 0];
    const auto opcode = instruction % 100;
    const std::array<int, 3> modes = {
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
      if (modes[i]) {
        immediates[i] = registers[position + 1 + i];
        ptrs[i] = &immediates[i];
      } else {
        ptrs[i] = &registers[registers[position + 1 + i]];
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
    case 99:
      return;
    default:
      throw std::runtime_error("Invalid opcode");
    }
  }
}

uint64_t execute(const uint64_t noun, const uint64_t verb,
                 Registers registers) {
  registers[1] = noun;
  registers[2] = verb;

  execute(registers);

  return registers[0];
}

Registers read() {
  Registers registers;
  size_t position = 0;
  uint64_t value;

  while (std::cin >> value) {
    char junk;
    std::cin >> junk;
    registers[position++] = value;
  }

  return registers;
}

} // namespace intcode
