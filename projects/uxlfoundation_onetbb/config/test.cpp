#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include <oneapi/tbb/global_control.h>
#include <vector>
#include <iostream>

int main() {
    oneapi::tbb::global_control gc(oneapi::tbb::global_control::max_allowed_parallelism, 2);

    std::vector<int> v(1000, 0);
    oneapi::tbb::parallel_for(std::size_t(0), v.size(), [&](std::size_t i){
        v[i] = static_cast<int>(i*i);
    });

    long long sum = 0;
    for (int x : v) sum += x;
    std::cout << "sum=" << sum << "\n";
    return 0;
}
