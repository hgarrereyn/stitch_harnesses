#include <pxr/base/tf/token.h>
#include <pxr/pxr.h>
#include <iostream>

int main() {
    pxr::TfToken t1("hello");
    pxr::TfToken t2("world");
    std::cout << "Token1: " << t1.GetString() << ", size=" << t1.size() << "\n";
    std::cout << "Token2: " << t2.GetString() << ", size=" << t2.size() << "\n";
    std::cout << "Equal? " << (t1 == t2 ? "yes" : "no") << "\n";
    return 0;
}
