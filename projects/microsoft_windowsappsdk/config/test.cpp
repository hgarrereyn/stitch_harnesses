#include <iostream>
#include "Microsoft.TraceLogging.h"

int main() {
    std::cout << "WindowsAppSDK minimal header available: Microsoft.TraceLogging.h" << std::endl;
    // We intentionally do not invoke any TraceLogging macros to avoid external dependencies.
    return 0;
}
