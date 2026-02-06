#include <iostream>
#include "oboe/Version.h"

int main(){
    const char* txt = oboe::getVersionText();
    if(txt==nullptr) return 1;
    std::cout << "Oboe version: " << txt << "\n";
    // Ensure headers parse by referencing constexpr values
    (void)oboe::Version::Number;
    return 0;
}
