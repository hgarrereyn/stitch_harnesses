#include <LIEF/LIEF.hpp>
#include <iostream>

int main() {
  try {
    auto elf = LIEF::ELF::Parser::parse("/bin/ls");
    if (elf) {
      std::cout << "ELF sections: " << elf->sections().size() << "\n";
      if (!elf->sections().empty()) {
        std::cout << "First section name: " << elf->sections()[0].name() << "\n";
      }
    } else {
      std::cout << "Failed to parse /bin/ls" << std::endl;
    }
  } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
