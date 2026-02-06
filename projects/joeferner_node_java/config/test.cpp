#include <iostream>
#include <node-java/java.h>

int main() {
    // Just ensure we can include the header and reference the type
    Java* j = nullptr;
    std::cout << "node-java headers available. Java* ptr=" << j << "\n";
    return 0;
}
