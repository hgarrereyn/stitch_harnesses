#include <iostream>
#include "libncmdump.h"
#include "ncmcrypt.h"

int main() {
    // Do not actually construct NeteaseCrypt since it requires a valid .ncm file.
    NeteaseCrypt* ptr = nullptr;
    (void)ptr; // suppress unused warning
    std::cout << "ncmdump library test OK" << std::endl;
    return 0;
}
