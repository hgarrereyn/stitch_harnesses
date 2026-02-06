#include <iostream>
#include <httpd.h>
#include <ap_release.h>

int main() {
    std::cout << "Apache version: " << AP_SERVER_VERSION << "\n";
    std::cout << "Default timeout: " << DEFAULT_TIMEOUT << "\n";
    return 0;
}
