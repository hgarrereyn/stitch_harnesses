#include <iostream>
extern "C" {
#include "maths.h"
#include "bitarray.h"
}

int main() {
    float rad = degreesToRadians(180);
    if (!(rad > 3.1415f && rad < 3.142f)) return 1;
    bitarrayElement_t arr[2] = {0};
    bitArraySet(arr, 3);
    bool v3 = bitArrayGet(arr, 3);
    bool v2 = bitArrayGet(arr, 2);
    std::cout << "ok: rad=" << rad << ", bit3=" << v3 << ", bit2=" << v2 << "\n";
    return (v3 && !v2) ? 0 : 1;
}
