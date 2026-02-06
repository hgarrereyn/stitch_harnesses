#include <bsls_util.h>
#include <iostream>

int sample(int) { return 7; }

int main() {
    int v = 123;
    int* p = BloombergLP::bsls::Util::addressOf(v);
    auto fptr = BloombergLP::bsls::Util::addressOf(sample);
    std::cout << "addressOf int OK: " << (p ? *p : -1) << ", fptr(): " << fptr(5) << std::endl;
    return 0;
}
