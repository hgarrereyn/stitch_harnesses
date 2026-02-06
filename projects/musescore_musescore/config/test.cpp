#include <iostream>
#include <vector>
#include "/fuzz/install/include/IntervalTree.h"

int main() {
#ifdef USE_INTERVAL_TREE_NAMESPACE
    using namespace interval_tree;
#endif
    using Interval = Interval<int,int>;
    std::vector<Interval> ivals;
    ivals.emplace_back(1, 5, 42);
    ivals.emplace_back(10, 20, 7);
    ivals.emplace_back(3, 8, 99);

    IntervalTree<int,int> tree(std::move(ivals));

    auto overlaps = tree.findOverlapping(4, 12);
    std::cout << "Overlaps count: " << overlaps.size() << "\n";
    int sum = 0;
    for (const auto &iv : overlaps) {
        sum += iv.value;
    }
    std::cout << "Sum: " << sum << "\n";
    return 0;
}
