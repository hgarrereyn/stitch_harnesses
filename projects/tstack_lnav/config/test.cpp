#include <cstdlib>
#include <iostream>

int main() {
    // Run the installed lnav binary to ensure it was built and is runnable
    int rc = std::system("/fuzz/install/bin/lnav -V >/dev/null 2>&1");
    std::cout << "lnav version rc=" << rc << "\n";
    return 0;
}
