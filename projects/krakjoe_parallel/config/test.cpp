#include <cstdio>
#include <parallel/monitor.h>

int main() {
    // Use a value from the API to ensure headers are usable
    int flags = PHP_PARALLEL_READY | PHP_PARALLEL_EXEC | PHP_PARALLEL_CLOSE;
    std::printf("parallel monitor flags sample: %d\n", flags);
    return 0;
}
