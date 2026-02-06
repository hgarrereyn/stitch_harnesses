#include <atomic_queue/atomic_queue.h>
#include <iostream>

int main() {
    using namespace atomic_queue;
    // Simple ring buffer of ints with capacity 8
    AtomicQueue2<int, 8> q;

    // Push a few values
    for (int i = 0; i < 5; ++i) {
        bool ok = q.try_push(i + 1);
        if (!ok) {
            std::cerr << "push failed unexpectedly" << std::endl;
            return 1;
        }
    }

    // Pop and accumulate
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        int v = 0;
        bool ok = q.try_pop(v);
        if (!ok) {
            std::cerr << "pop failed unexpectedly" << std::endl;
            return 1;
        }
        sum += v;
    }

    std::cout << "sum=" << sum << std::endl; // Expect 15
    return sum == 15 ? 0 : 2;
}
