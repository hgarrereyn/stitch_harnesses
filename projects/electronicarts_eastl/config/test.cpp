#include <EASTL/vector.h>
#include <EASTL/string.h>
#include <EASTL/algorithm.h>
#include <iostream>

int main() {
    eastl::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i*i);
    int sum = 0;
    for (int x : v) sum += x;

    eastl::string s("hello EASTL");
    s += "!";

    std::cout << "sum=" << sum << " str=" << s.c_str() << " size=" << v.size() << "\n";
    return 0;
}
