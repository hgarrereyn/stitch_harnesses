#include <iostream>
#include <cstring>
extern "C" {
#include "paxcounter_shim.h"
}

int main(){
    const char* v = paxcounter_version();
    int s = paxcounter_add(2, 40);
    std::cout << "Version: " << v << " sum=" << s << std::endl;
    // simple runtime check
    if (s != 42 || std::strlen(v) == 0) return 1;
    return 0;
}
