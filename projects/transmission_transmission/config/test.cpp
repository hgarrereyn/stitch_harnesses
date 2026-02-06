#include <iostream>
#include <string>
#include "transmission/transmission.h"
#include "transmission/variant.h"

int main() {
    std::string dl = tr_getDefaultDownloadDir();
    std::string cfg = tr_getDefaultConfigDir("transmission-test");
    std::cout << "Default download dir: " << dl << "\n";
    std::cout << "Default config dir: " << cfg << "\n";
    auto settings = tr_sessionGetDefaultSettings();
    (void)settings;
    std::cout << "Libtransmission basic API call succeeded." << std::endl;
    return 0;
}
