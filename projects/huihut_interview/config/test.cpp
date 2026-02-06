#include <iostream>
#include "interview_algorithms.hpp"

int main() {
    std::vector<int> v = {5,1,4,2,8,0,2,9};
    BubbleSort(v);
    bool ok1 = std::is_sorted(v.begin(), v.end());

    std::vector<int> v2 = {9,7,5,3,1,2,4,6,8,0};
    SelectionSort(v2);
    bool ok2 = std::is_sorted(v2.begin(), v2.end());

    std::cout << (ok1 && ok2 ? "OK" : "FAIL") << "\n";
    return (ok1 && ok2) ? 0 : 1;
}
