#include <iostream>
#include <components/esm/generatedrefid.hpp>

int main() {
    ESM::GeneratedRefId gid(42);
    if (!(gid == ESM::GeneratedRefId(42))) {
        std::cout << "Comparison failed\n";
        return 1;
    }
    std::cout << "GeneratedRefId value=" << static_cast<unsigned long long>(gid.getValue()) << "\n";
    return 0;
}
