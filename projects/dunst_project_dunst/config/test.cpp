#include <cstdio>
#include <string>
extern "C" {
#include <dunst/utils.h>
}

int main() {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "a-b-c-d");
    // Replace '-' with ':' using a dunst utility function
    string_replace_char('-', ':', buf);
    // Simple check to ensure symbol was linked and function executed
    if (std::string(buf) != std::string("a:b:c:d")) return 1;
    std::printf("%s\n", buf);
    return 0;
}
