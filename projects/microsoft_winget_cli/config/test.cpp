#include <iostream>
extern "C" {
#include <pure/pure.h>
}

int main() {
    uint8_t buf[] = { 'a', 'b', 'c', 'd' };
    const uint8_t str[] = { 'a', 'b' };
    int eq = pure_eq(buf, sizeof(buf), 0, str, sizeof(str));
    int ov = pure_overflow(1, 2, 10);
    std::cout << "pure_eq: " << eq << ", pure_overflow: " << ov << std::endl;
    return 0;
}
