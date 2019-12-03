#include <array>
#include <iostream>

namespace intcode {

constexpr size_t REGISTER_COUNT = 1000;
using Registers = std::array<uint64_t, REGISTER_COUNT>;

void execute(Registers &registers) {
  size_t position = 0;
  while (true) {
    const auto opcode = registers[position + 0];
    const auto in1 = registers[position + 1];
    const auto in2 = registers[position + 2];
    const auto out = registers[position + 3];
    switch (opcode) {
    case 1:
      registers[out] = registers[in1] + registers[in2];
      break;
    case 2:
      registers[out] = registers[in1] * registers[in2];
      break;
    case 99:
      return;
    default:
      throw std::runtime_error("Invalid opcode");
    }
    position += 4;
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
