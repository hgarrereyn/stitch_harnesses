#include <stdio.h>
#include <stdint.h>
extern "C" {
    void janus_mark_started(void);
    long long janus_get_monotonic_time(void);
    unsigned int janus_random_uint32(void);
}
int main() {
    janus_mark_started();
    long long t = janus_get_monotonic_time();
    unsigned int r = janus_random_uint32();
    printf("t=%lld r=%u\n", t, r);
    return 0;
}
