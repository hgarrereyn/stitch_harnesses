#include <iostream>
#include <amnezia/loglevel.h>

int main() {
    LogLevel lvl = Info;
    std::cout << "LogLevel Info value: " << static_cast<int>(lvl) << "\n";
    return 0;
}
