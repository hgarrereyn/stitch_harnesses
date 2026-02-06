#include <iostream>
#include "Word.h"
#include "Character.h"

int main() {
  YouCompleteMe::Word w( std::string("Hello, World!") );
  std::cout << "Word length (graphemes): " << w.Length() << "\n";
  auto chars = w.Characters();
  if (!chars.empty()) {
    std::cout << "First char base: " << chars.front()->Base() << "\n";
  }
  return 0;
}
