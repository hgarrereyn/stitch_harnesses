#include <iostream>
#include <cstring>
#include "Util.h"

int main(){
    const wchar_t* w = L"Hello TinyTracer";
    char buf[64] = {0};
    util::wstr_to_str(w, buf, sizeof(buf));
    // ensure it did something reasonable
    if(std::strlen(buf) == 0){
        std::cout << "Conversion failed" << std::endl;
        return 1;
    }
    std::cout << "Converted: " << buf << std::endl;
    return 0;
}
