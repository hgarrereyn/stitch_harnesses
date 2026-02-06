#include <iostream>
extern "C" {
#include <gnupg/stringhelp.h>
}

int main() {
    char *joined = strconcat("hello", ", ", "world", "!", (const char*)NULL);
    if (joined) {
        trim_spaces(joined);
        std::cout << joined << std::endl;
    }
    const char *p = memistr("abcdef", 6, "CD");
    std::cout << (p ? "found" : "not found") << std::endl;
    return 0;
}
