#include <iostream>
extern "C" {
#include <varnum.h>
}

int main() {
    uint32_t values[] = {0u, 1u, 127u, 128u, 300u, 16384u, 2097151u, 268435455u};
    int total = 0;
    for (auto v : values) {
        total += sizeVarInt(v);
    }
    std::cout << "Total sizes: " << total << "\n";
    return 0;
}
