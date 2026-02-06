#include <iostream>
#include <string>
#include <parallel_hashmap/phmap.h>

int main() {
    phmap::flat_hash_map<std::string, int> counts;
    counts["apple"] = 3;
    counts.insert({"banana", 5});
    counts.try_emplace("cherry", 7);

    int total = 0;
    for (const auto &kv : counts) total += kv.second;

    // demonstrate a lookup
    if (counts.contains("banana")) total += counts["banana"];

    std::cout << "total=" << total << " size=" << counts.size() << "\n";
    return 0;
}
