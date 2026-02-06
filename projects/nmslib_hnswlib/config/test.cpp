#include <iostream>
#include <queue>
#include <random>
#include "hnswlib/hnswlib.h"

int main() {
    const int dim = 8;
    const int max_elements = 100;
    const int M = 8;
    const int ef_construction = 100;

    hnswlib::L2Space space(dim);
    hnswlib::HierarchicalNSW<float> index(&space, max_elements, M, ef_construction);

    std::mt19937 rng(123);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<float> data(dim * max_elements);
    for (int i = 0; i < dim * max_elements; ++i) data[i] = dist(rng);

    for (int i = 0; i < max_elements; ++i) {
        index.addPoint(&data[i * dim], i);
    }

    index.setEf(10);

    int correct = 0;
    for (int i = 0; i < max_elements; ++i) {
        auto res = index.searchKnn(&data[i * dim], 1);
        if (!res.empty() && res.top().second == static_cast<hnswlib::labeltype>(i)) ++correct;
    }

    std::cout << "Self-recall: " << (double)correct / max_elements << "\n";
    return 0;
}
