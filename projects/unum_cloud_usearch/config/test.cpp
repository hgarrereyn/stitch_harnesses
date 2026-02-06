#include <cstdio>
#include <usearch/index.hpp>
#include <usearch/index_dense.hpp>

using namespace unum::usearch;

int main() {
    metric_punned_t metric(3, metric_kind_t::l2sq_k, scalar_kind_t::f32_k);
    index_dense_t index = index_dense_t::make(metric);

    float vec[3] = {0.2f, 0.6f, 0.4f};
    index.reserve(10);
    auto add_ok = index.add(42, &vec[0]);
    if (!add_ok) return 1;

    auto matches = index.search(&vec[0], 5);
    if (!matches || matches.size() == 0) return 1;

    std::printf("Top match key: %zu, distance: %f\n", (std::size_t)matches[0].member.key, (double)matches[0].distance);
    return 0;
}
