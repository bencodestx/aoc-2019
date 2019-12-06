#include "intcode.hpp"

int main() {
  auto registers = intcode::read();

  intcode::execute(registers, []() { return 1; });
}
