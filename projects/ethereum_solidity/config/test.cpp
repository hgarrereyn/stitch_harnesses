#include <iostream>
#include <string>
#include <libsolutil/UTF8.h>
int main(){
    using namespace solidity::util;
    std::string good = "hello";
    std::string bad = std::string("hi\xFF", 3);
    size_t pos = 0;
    bool ok1 = validateUTF8(good, pos);
    bool ok2 = validateUTF8(bad, pos);
    std::cout << ok1 << " " << ok2 << "\n";
    return 0;
}
