#include <cstdio>
#include <cstdlib>
#include <cmath>
extern "C" {
#include <cblas.h>
}

int main() {
    const int M = 2, N = 2, K = 2;
    float A[M*K] = {1, 2,
                    3, 4};
    float B[K*N] = {5, 6,
                    7, 8};
    float C[M*N] = {0, 0,
                    0, 0};
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                M, N, K,
                1.0f, A, K, B, N, 0.0f, C, N);
    // Expected result [[19,22],[43,50]]
    printf("%0.0f %0.0f %0.0f %0.0f\n", C[0], C[1], C[2], C[3]);
    return (std::fabs(C[0]-19.0f) < 1e-4f && std::fabs(C[3]-50.0f) < 1e-4f) ? 0 : 1;
}
