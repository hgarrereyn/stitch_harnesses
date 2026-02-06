#include <iostream>
#include "RG.h"
extern "C" {
#include "value.h"
}

int main() {
    SIValue a = SI_LongVal(123);
    SIValue b = SI_DoubleVal(3.14);
    SIValue c = SI_BoolVal(1);
    (void)b; (void)c;
    std::cout << "SIValue longval=" << a.longval << " type=" << a.type << std::endl;
    uint64_t x = 7; uint64_t y = SET_MSB(x); (void)y;
    return 0;
}
