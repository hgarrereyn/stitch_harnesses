#include <cstdio>
#include "blis.h"

int main() {
    const dim_t m = 2, n = 3, k = 4;
    const inc_t rsa = 1, csa = m;   // column-major
    const inc_t rsb = 1, csb = k;   // column-major
    const inc_t rsc = 1, csc = m;   // column-major

    double *A = (double*)malloc(sizeof(double) * m * k);
    double *B = (double*)malloc(sizeof(double) * k * n);
    double *C = (double*)malloc(sizeof(double) * m * n);

    double alpha = 1.0;
    double beta  = 0.0;

    bli_drandm(0, BLIS_DENSE, m, k, A, rsa, csa);
    bli_dsetm(BLIS_NO_CONJUGATE, 0, BLIS_NONUNIT_DIAG, BLIS_DENSE, k, n, &alpha, B, rsb, csb);
    bli_dsetm(BLIS_NO_CONJUGATE, 0, BLIS_NONUNIT_DIAG, BLIS_DENSE, m, n, &beta,  C, rsc, csc);

    bli_dgemm(BLIS_NO_TRANSPOSE, BLIS_NO_TRANSPOSE, m, n, k,
              &alpha, A, rsa, csa, B, rsb, csb, &beta, C, rsc, csc);

    printf("C(0,0)=%f\n", C[0]);
    printf("C(1,2)=%f\n", C[1 + 2*csc]);

    free(A); free(B); free(C);
    return 0;
}
