#include <iostream>
extern "C" {
#include "match.h"
}

int main() {
  const char* needle = "fz";
  const char* hay = "fast fuzzy selector";
  score_t s = match(needle, hay);
  std::cout << "score=" << (double)s << "\n";
  std::cout << (has_match(needle, hay) ? "has_match=1" : "has_match=0") << "\n";
  size_t pos[8] = {0};
  score_t s2 = match_positions(needle, hay, pos);
  std::cout << "score2=" << (double)s2 << ", pos0=" << pos[0] << "\n";
  return 0;
}
