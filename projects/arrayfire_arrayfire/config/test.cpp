#include <iostream>
#include <af/array.h>
#include <af/arith.h>
#include <af/random.h>
#include <af/algorithm.h>

int main() {
    try {
        af::info();
        af::array a = af::randu(3, 3, f32);
        af::array b = af::sin(a);
        float s = af::sum<float>(b);
        std::cout << "sum(sin(randu)) = " << s << std::endl;
    } catch (const af::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
