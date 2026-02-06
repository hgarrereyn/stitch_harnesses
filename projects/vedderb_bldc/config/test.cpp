#include <cstdio>
#include <cstdint>
extern "C" {
#include "buffer.h"
#include "utils_math.h"
}

int main() {
    uint8_t buf[16] = {0};
    int32_t idx = 0;
    buffer_append_int32(buf, 123456789, &idx);
    idx = 0;
    int32_t val = buffer_get_int32(buf, &idx);

    float ang = 3.14159f; // ~pi
    float mapped = utils_map_angle(ang, -3.14159f, 3.14159f);

    std::printf("val=%d mapped=%.3f\n", val, mapped);
    return 0;
}
