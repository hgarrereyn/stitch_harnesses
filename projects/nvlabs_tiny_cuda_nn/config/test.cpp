#include <tiny-cuda-nn/common.h>
#include <iostream>

int main() {
    // Use header-only vector utilities through common.h (which includes vec.h)
    tcnn::tvec<float, 3> a; a[0]=1.0f; a[1]=2.0f; a[2]=3.0f;
    tcnn::tvec<float, 3> b(2.0f);
    auto c = a + b;
    std::cout << "c[0]=" << c[0] << ", c[1]=" << c[1] << ", c[2]=" << c[2] << "\n";
    return 0;
}
