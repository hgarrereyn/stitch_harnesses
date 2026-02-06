#include <iostream>
#include "pico/platform.h"
#include "pico/stdlib.h"
#include "pico/time.h"

int main() {
    int a = 5, b = 3;
    int m = MIN(a, b); // macro from pico/platform.h
    std::cout << "Pico SDK host test. MIN(" << a << ", " << b << ") = " << m << "\n";
    return 0;
}
