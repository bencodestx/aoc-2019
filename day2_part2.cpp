#include <iostream>

#include "intcode.hpp"

int main() {
  const auto registers = intcode::read();

  for (uint64_t noun = 0; noun <= 99; ++noun) {
    for (uint64_t verb = 0; verb <= 99; ++verb) {
      const auto result = intcode::execute(noun, verb, registers);
      if (19690720 == result) {
        std::cout << noun * 100 + verb << std::endl;
        return 0;
      }
    }
  }

  return 1;
}
