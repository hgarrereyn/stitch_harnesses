#include <iostream>
#include "static_ids.h"

int main(){
    // Print a couple of IDs from the public enum to verify headers work
    std::cout << (int)WinID::NeedsWorkSwitch << "\n";
    std::cout << (int)WinID::ListContextReferencesStart << "\n";
    return 0;
}
