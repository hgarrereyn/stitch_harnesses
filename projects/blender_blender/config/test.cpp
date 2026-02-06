#include <cstdio>
#include "intern/guardedalloc/MEM_guardedalloc.h"

int main() {
  const char *tag = "test_allocation";
  const size_t n = 128;
  void *p = MEM_callocN(n, tag);
  if (!p) {
    std::printf("Allocation failed\n");
    return 1;
  }
  std::printf("Allocated %zu bytes, in use: %zu bytes, blocks: %u\n",
              n, MEM_get_memory_in_use(), (unsigned)MEM_get_memory_blocks_in_use());
  ((unsigned char*)p)[0] = 42;
  ((unsigned char*)p)[n-1] = 24;
  void *q = MEM_dupallocN(p);
  MEM_freeN(p);
  MEM_freeN(q);
  std::printf("After free, in use: %zu bytes, blocks: %u\n",
              MEM_get_memory_in_use(), (unsigned)MEM_get_memory_blocks_in_use());
  return 0;
}
