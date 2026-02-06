#include <iostream>
#include <vector>
#include <annoy/annoylib.h>
#include <annoy/kissrandom.h>

int main() {
    using namespace Annoy;
    // 2D points, Angular metric, single-threaded build policy
    AnnoyIndex<int, float, Angular, Kiss32Random, AnnoyIndexSingleThreadedBuildPolicy> index(2);

    float a[] = {1.0f, 0.0f};
    float b[] = {0.0f, 1.0f};
    float c[] = {0.9f, 0.1f};

    index.add_item(0, a);
    index.add_item(1, b);
    index.add_item(2, c);

    index.build(10);

    std::vector<int> result;
    std::vector<float> distances;
    index.get_nns_by_item(2, 2, -1, &result, &distances);

    std::cout << "n_items=" << index.get_n_items() << ", n_trees=" << index.get_n_trees() << "\n";
    std::cout << "Nearest to item 2: ";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << "(d=" << distances[i] << ") ";
    }
    std::cout << "\n";
    return 0;
}
