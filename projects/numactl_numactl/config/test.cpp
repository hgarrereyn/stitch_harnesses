#include <cstdio>
#include <numa.h>

int main() {
    int avail = numa_available();
    if (avail < 0) {
        // Library not usable on this machine, but we still exercised the API
        std::printf("libnuma not available (code %d)\n", avail);
        return 0;
    }
    int max_node = numa_max_node();
    long long free_mem = 0;
    long long node_size = numa_node_size64(0, &free_mem);
    auto mask = numa_allocate_nodemask();
    if (mask) {
        numa_free_nodemask(mask);
    }
    std::printf("libnuma available. max_node=%d, node0_size=%lld, node0_free=%lld\n", max_node, node_size, free_mem);
    return 0;
}
