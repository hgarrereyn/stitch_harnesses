#include <iostream>
#include <global.h>

int main() {
    std::cout << "App: " << X_APPLICATIONDISPLAYNAME << "\n";
    std::cout << "Name: " << X_APPLICATIONNAME << "\n";
    std::cout << "Version: " << X_APPLICATIONVERSION << "\n";
    std::cout << "Org: " << X_ORGANIZATIONNAME << " (" << X_ORGANIZATIONDOMAIN << ")\n";
    return 0;
}
