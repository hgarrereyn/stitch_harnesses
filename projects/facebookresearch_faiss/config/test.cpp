#include <faiss/IndexFlat.h>
#include <iostream>

int main() {
    int d = 4; // dimension
    faiss::IndexFlatL2 index(d);

    // add 3 vectors
    float xb[3 * 4] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };
    index.add(3, xb);

    // search for nearest neighbors of one query
    float xq[4] = {0.9f, 0.1f, 0.0f, 0.0f};
    faiss::idx_t k = 2;
    std::vector<faiss::idx_t> I(k);
    std::vector<float> D(k);
    index.search(1, xq, k, D.data(), I.data());

    std::cout << "NN ids: ";
    for (int i = 0; i < k; i++) std::cout << I[i] << " ";
    std::cout << "\nDistances: ";
    for (int i = 0; i < k; i++) std::cout << D[i] << " ";
    std::cout << std::endl;

    return 0;
}
