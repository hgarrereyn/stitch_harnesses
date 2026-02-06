#include <cstdio>
#include <perf_ninja/solution.h>

int main() {
    const int N = 5;
    int arr[N] = {1, 2, 3, 4, 5};
    int s = solution(arr, N);
    // Expected sum = 15
    std::printf("sum=%d\n", s);
    return (s == 15) ? 0 : 1;
}
