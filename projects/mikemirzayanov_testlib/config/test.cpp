#include "testlib.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Register as a generator to satisfy testlib initialization
    registerGen(argc, argv, 1);

    // Use a couple of API pieces that do not require further I/O
    pattern p("[a-z]{3}");
    std::string s = p.next(rnd); // use global rnd
    std::cout << "Generated: " << s << " Length=" << toString(s.size()) << std::endl;
    // Also test a simple human-readable number conversion
    std::cout << toHumanReadableString(1000000000LL) << std::endl;
    return 0;
}
