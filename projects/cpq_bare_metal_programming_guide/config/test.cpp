#include <cstdio>
#include <cstdint>
extern "C" {
#include <baremetal/hal.h>
}

int main() {
  // Use a header-only, pure function: timer_expired
  uint32_t now = 0;
  uint32_t prd = 10;
  uint32_t t = 0;
  int expired_count = 0;
  for (int i = 0; i < 50; ++i) {
    now += 1;
    if (timer_expired(&t, prd, now)) {
      expired_count++;
    }
  }
  // Expect around 5 expirations in 50 ticks with period 10
  std::printf("expired=%d\n", expired_count);
  return 0;
}
