#include <iostream>
#include <wabt/utf8.h>

int main() {
    const char* s1 = "hello";
    const char* s2 = "\xFF\xFE"; // invalid UTF-8
    bool v1 = wabt::IsValidUtf8(s1, 5);
    bool v2 = wabt::IsValidUtf8(s2, 2);
    std::cout << "v1=" << v1 << ", v2=" << v2 << "\n";
    return (v1 && !v2) ? 0 : 1;
}
