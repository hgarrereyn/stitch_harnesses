#include <cstdio>
#include <notcurses/notcurses.h>

int main() {
  const char* ver = notcurses_version();
  if(!ver){
    return 1;
  }
  int maj=0, min=0, pat=0, tw=0;
  notcurses_version_components(&maj, &min, &pat, &tw);
  std::printf("notcurses version: %s (components %d.%d.%d.%d)\n", ver, maj, min, pat, tw);
  return 0;
}
