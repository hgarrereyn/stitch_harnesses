#include <cstdio>
#include "skcms.h"

int main() {
    // Test TransferFunction eval/invert
    skcms_TransferFunction tf = {2.2f, 1.0f, 0.0f, 0.0f, 0.04045f, 0.0f, 0.0f};
    float x = 0.5f;
    float y = skcms_TransferFunction_eval(&tf, x);

    skcms_TransferFunction inv;
    bool ok = skcms_TransferFunction_invert(&tf, &inv);

    // Test Matrix invert/concat
    skcms_Matrix3x3 m = {{{1,0,0},{0,1,0},{0,0,1}}};
    skcms_Matrix3x3 invm;
    bool inv_ok = skcms_Matrix3x3_invert(&m, &invm);
    skcms_Matrix3x3 cat = skcms_Matrix3x3_concat(&m, &invm);

    std::printf("ok=%d inv_ok=%d y=%f cat00=%f\n", ok?1:0, inv_ok?1:0, y, cat.vals[0][0]);
    return 0;
}
