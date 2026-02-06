#include <iostream>
#include "lite/lite.h"

int main() {
    std::vector<float> v = {1.0f, 2.0f, 3.0f};
    unsigned int max_id = 0;
    auto probs = lite::utils::math::softmax(v, max_id);
    std::cout << "max_id=" << max_id << ", probs_size=" << probs.size() << std::endl;
    std::vector<float> a = {1.0f, 0.0f, 0.0f};
    std::vector<float> b = {0.5f, 0.5f, 0.0f};
    float sim = lite::utils::math::cosine_similarity(a, b);
    std::cout << "cosine_similarity=" << sim << std::endl;
    return 0;
}
