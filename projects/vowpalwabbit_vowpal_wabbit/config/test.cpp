#include <vw/core/vw.h>

int main() {
  // Initialize a simple VW workspace quietly, then immediately finish.
  // Using the deprecated string-based initialize for simplicity
  VW::workspace* vw = VW::initialize("--quiet");
  if (!vw) return 1;
  VW::finish(*vw);
  return 0;
}
