#include <cstdio>
#include <simsimd/simsimd.h>

int main() {
    simsimd_f32_t a[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    simsimd_f32_t b[4] = {0.0f, 1.0f, 0.0f, 0.0f};
    simsimd_distance_t d = 0;
    simsimd_cos_f32(a, b, 4, &d);
    std::printf("cosine distance = %f\n", (double)d);

    simsimd_distance_t dot = 0;
    simsimd_dot_f32(a, b, 4, &dot);
    std::printf("dot = %f\n", (double)dot);
    return 0;
}
