#include "version.h"
#include <iostream>
int main() {
    std::cout << APP_NAME << " " << APP_VERSION << " on " << APP_OS << " (" << APP_ARCH << ", " << APP_BITS << ")\n";
    return 0;
}
