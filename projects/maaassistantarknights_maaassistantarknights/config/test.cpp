#include <iostream>
#include "AsstCaller.h"

int main() {
    std::cout << "MAA version: " << AsstGetVersion() << "\n";
    AsstHandle h = AsstCreate();
    if (h) {
        AsstBool ok = AsstStart(h);
        std::cout << "Start returned: " << (int)ok << "\n";
        AsstDestroy(h);
    }
    return 0;
}
