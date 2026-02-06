#include <cstdio>
#include <cstdint>
#include <iostream>
#include <Blinker/BlinkerDebug.h>

int main(){
    uint32_t h = BLINKER_FreeHeap();
    std::cout << "FreeHeap=" << h << std::endl;
    return 0;
}
