#include <iostream>
#include "brave/components/brave_ads/core/public/ads_constants.h"

int main() {
    std::cout << "Trace category: " << brave_ads::kTraceEventCategory << "\n";
    std::cout << "DB filename: " << brave_ads::kDatabaseFilename << "\n";
    std::cout << "Client JSON: " << brave_ads::kClientJsonFilename << "\n";
    std::cout << "Confirmations JSON: " << brave_ads::kConfirmationsJsonFilename << "\n";
    return 0;
}
