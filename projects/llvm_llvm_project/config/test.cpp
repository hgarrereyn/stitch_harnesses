#include <iostream>
#include <string>
#include "llvm/Demangle/Demangle.h"

int main() {
    const char* mangled = "_ZSt4cout"; // std::cout in Itanium ABI
    char* demangled = llvm::itaniumDemangle(mangled);
    std::string out = demangled ? demangled : "(null)";
    std::cout << "Demangled: " << out << "\n";
    std::free(demangled);
    return 0;
}
