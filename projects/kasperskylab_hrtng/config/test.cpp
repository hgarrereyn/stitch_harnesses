#include <iostream>
#include "ordered_set.h"
#include <functional>

int main() {
    OrderedSet<int, std::less<int>> s;
    s.push_back(3);
    s.push_back(1);
    s.push_back(2);
    s.push_back(2);

    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }

    if (s.size() != 3 || !s.has_item(1) || !s.has_item(2) || !s.has_item(3)) {
        std::cerr << "OrderedSet basic checks failed\n";
        return 1;
    }

    std::cout << "Sum=" << sum << " Size=" << s.size() << "\n";
    return 0;
}
