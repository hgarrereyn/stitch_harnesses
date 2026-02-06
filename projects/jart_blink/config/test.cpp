extern "C" {
#include "blink/util.h"
#include <stdio.h>
}

int main() {
  char buf[64];
  // Format a size using blink's utility API
  FormatSize(buf, 1234567u, 1024u);
  // Print the formatted size
  printf("Formatted size: %s\n", buf);
  return 0;
}
