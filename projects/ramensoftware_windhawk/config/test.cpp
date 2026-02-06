#include <iostream>
#include <string>
#include <wchar.h>
#include "/fuzz/install/include/windhawk/version.h"

int main() {
    // Use the exported macro API to build a version string.
    std::string ver = VER_FILE_VERSION_STR; // from version.h
    std::cout << "Windhawk version: " << ver << std::endl;
    // Also use the wide version macro to ensure it compiles in C++.
    const wchar_t* wver = VER_FILE_VERSION_WSTR;
    (void)wver; // suppress unused warning
    return 0;
}
