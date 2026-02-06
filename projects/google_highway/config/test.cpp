#include <cstdio>
#include "hwy/highway.h"

namespace hn = hwy::HWY_NAMESPACE;

int main() {
    alignas(16) float a_arr[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    alignas(16) float b_arr[4] = {5.0f, 6.0f, 7.0f, 8.0f};
    alignas(16) float out_arr[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    using D = hn::FixedTag<float, 4>;
    D d;

    auto a = hn::Load(d, a_arr);
    auto b = hn::Load(d, b_arr);
    auto c = hn::Add(a, b);
    hn::Store(c, d, out_arr);

    float sum0 = out_arr[0];
    std::printf("sum0=%f\n", sum0);
    return (sum0 == 6.0f) ? 0 : 1;
}
