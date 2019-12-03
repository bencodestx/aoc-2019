#include <iostream>

#include "intcode.hpp"

int main() {
  const auto registers = intcode::read();

  const auto result = intcode::execute(12, 2, registers);

  std::cout << result << std::endl;
}
