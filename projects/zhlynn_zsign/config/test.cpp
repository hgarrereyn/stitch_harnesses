#include "common.h"
#include "mach-o.h"
#include "openssl.h"
#include "signing.h"
#include "macho.h"
#include "bundle.h"
#include <iostream>

int main() {
    ZSignAsset asset; // default constructed; no external files needed
    ZMachO macho;     // not initialized with a file
    ZBundle bundle;   // bundle operations not invoked

    bool err = ZSignAsset::CMSError();
    std::cout << "zsign library test OK, CMSError()=" << err << std::endl;
    return 0;
}
