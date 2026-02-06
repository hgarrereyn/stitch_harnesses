#include <Globals.h>
#include <StringUtils.h>
#include <iostream>

int main() {
    int value = 0;
    bool ok = StringToInteger<int>("12345", value);
    std::cout << "Parsed ok: " << ok << ", value=" << value << "\n";
    return 0;
}
