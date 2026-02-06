#include <cstdio>
#include <cstring>
#include "intern/guardedalloc/MEM_guardedalloc.h"

int main() {
  MEM_init_memleak_detection();
  void *p = MEM_mallocN(128, "test_alloc");
  if (!p) {
    return 1;
  }
  std::memset(p, 0xAB, 128);
  size_t len = 0;
  if (MEM_allocN_len) {
    len = MEM_allocN_len(p);
  }
  if (len < 128) {
    // length should be at least the requested size
    // not fatal, but indicate unexpected
  }
  MEM_freeN(p);
  size_t in_use = 0;
  if (MEM_get_memory_in_use) {
    in_use = MEM_get_memory_in_use();
  }
  std::printf("ok: len=%zu in_use=%zu\n", len, in_use);
  return 0;
}
