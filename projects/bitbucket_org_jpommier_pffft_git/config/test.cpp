#include <stdio.h>
#include <math.h>
#include <pffft.h>

int main() {
    const int N = 128; // supported length (power of 2 >= 32)
    PFFFT_Setup *setup = pffft_new_setup(N, PFFFT_REAL);
    if (!setup) {
        printf("Failed to create PFFFT setup\n");
        return 1;
    }

    float *in  = (float*)pffft_aligned_malloc(sizeof(float)*N);
    float *out = (float*)pffft_aligned_malloc(sizeof(float)*N);
    float *wrk = (float*)pffft_aligned_malloc(sizeof(float)*N);

    for (int i = 0; i < N; ++i) in[i] = sinf(2.0f*(float)M_PI*(float)i/(float)N);

    pffft_transform_ordered(setup, in, out, wrk, PFFFT_FORWARD);
    pffft_transform_ordered(setup, out, in, wrk, PFFFT_BACKWARD);

    // Scale back (backward transform is unnormalized)
    for (int i = 0; i < N; ++i) in[i] /= (float)N;

    // Print a simple checksum to verify it ran
    float sum = 0.0f; for (int i = 0; i < N; ++i) sum += in[i];
    printf("checksum %.6f simd_size %d\n", sum, pffft_simd_size());

    pffft_aligned_free(in);
    pffft_aligned_free(out);
    pffft_aligned_free(wrk);
    pffft_destroy_setup(setup);
    return 0;
}
