#include <iostream>
#include <DFHackVersion.h>

int main() {
    std::cout << "DF version: " << DF_VERSION << "\n";
    std::cout << "DFHack version: " << DFHACK_VERSION << "\n";
    std::cout << "ABI version: " << DFHACK_ABI_VERSION << "\n";
    std::cout << "Git desc: " << DFHACK_GIT_DESCRIPTION << "\n";
    // also exercise functions
    std::cout << DFHack::Version::df_version() << "\n";
    std::cout << DFHack::Version::dfhack_version() << "\n";
    std::cout << DFHack::Version::git_commit(true) << "\n";
    return 0;
}
