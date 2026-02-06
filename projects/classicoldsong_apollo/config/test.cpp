#include <iostream>
#include "move_by_copy.h"

int main() {
    std::string s = "hello";
    auto moved = move_by_copy_util::cmove(s);
    std::string out = moved; // move occurs via MoveByCopy
    std::cout << out << "\n";
    return 0;
}
