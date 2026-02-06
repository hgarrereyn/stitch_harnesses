#include <iostream>
#include <hel.h>

int main() {
    std::cout << "kHelNumCalls=" << (int)kHelNumCalls << "\n";
    // Use a trivial type from hel headers
    HelHandle h = 0; (void)h;
    return 0;
}
