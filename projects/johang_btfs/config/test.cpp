#include <iostream>
#include <cstring>
#include "btfs.h"

int main() {
    btfs::Array arr;
    if (!arr.expand(16)) {
        std::cerr << "expand failed\n";
        return 1;
    }
    std::memset(arr.buf, 'A', arr.size);

    btfs::Log log(""); // write to /dev/null
    log << "btfs test log\n";

    std::cout << "ok:" << arr.size << "\n";
    return 0;
}
