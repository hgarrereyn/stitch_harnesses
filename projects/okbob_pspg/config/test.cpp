#include <iostream>
#include <pspg/commands.h>

int main() {
    // Use an enum from commands.h to ensure headers are usable
    PspgCommand cmd = cmd_Quit; // some valid enum constant
    std::cout << "Command value: " << (int)cmd << "\n";
    return 0;
}
