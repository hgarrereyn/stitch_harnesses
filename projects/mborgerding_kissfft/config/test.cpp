#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kissfft/kiss_fft.h"

int main() {
    int nfft = 8;
    int inverse = 0;

    kiss_fft_cfg cfg = kiss_fft_alloc(nfft, inverse, NULL, NULL);
    if (!cfg) {
        fprintf(stderr, "alloc failed\n");
        return 1;
    }

    kiss_fft_cpx in[8];
    kiss_fft_cpx out[8];

    for (int k = 0; k < nfft; ++k) {
        in[k].r = cos(2 * M_PI * k / nfft);
        in[k].i = sin(2 * M_PI * k / nfft);
    }

    kiss_fft(cfg, in, out);

    double sum = 0.0;
    for (int k = 0; k < nfft; ++k) {
        sum += fabs(out[k].r) + fabs(out[k].i);
    }
    printf("sum=%f\n", sum);

    kiss_fft_free(cfg);
    return 0;
}
