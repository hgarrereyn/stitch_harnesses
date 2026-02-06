#include <fftw3.h>
#include <cstdio>

int main() {
    // Test only the allocation API to avoid requiring generated codelets
    const int N = 16;
    double *buf = fftw_alloc_real(N);
    if (!buf) {
        std::printf("allocation failed\n");
        return 1;
    }
    for (int i = 0; i < N; ++i) buf[i] = i;
    std::printf("buf[0]=%f buf[15]=%f\n", buf[0], buf[15]);
    fftw_free(buf);
    fftw_cleanup();
    return 0;
}
