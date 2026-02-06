#include <cstdio>
#include "nchan_version.h"

int main() {
  const char *ver = NCHAN_VERSION;
  std::printf("Nchan version: %s\n", ver);
  // Simple check to make sure macro is defined and non-empty
  if (ver && ver[0] != '\0') {
    return 0;
  }
  return 1;
}
