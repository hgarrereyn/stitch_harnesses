#include <iostream>
#include <deskflow/KeyTypes.h>
#include <deskflow/MouseTypes.h>
#include <deskflow/OptionTypes.h>

int main() {
    KeyModifierMask mask = KeyModifierShift | KeyModifierControl;
    std::cout << "Deskflow headers available. Mod mask=" << mask << "\n";
    return 0;
}
