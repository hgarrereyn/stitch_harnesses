#include <iostream>
#include <string>
#include "SourceDefs.h"

int main(){
    std::string s = "  hello, ShaderGlass  \"  ";
    auto t = trim(s);
    std::cout << t << "\n";
    return 0;
}
