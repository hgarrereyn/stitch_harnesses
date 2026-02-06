#include <cstdio>
extern "C" {
#include "buffer.h"
}

int main() {
    buffer b{}; // zero-initialize
    // Use inline helpers from buffer.h which do not require linking
    int d = light_isdigit('5');
    int x = light_isxdigit('a');
    // Simulate a small string and test suffix check (also inline)
    b.ptr = (char*)"path/";
    b.used = 6; // includes terminating NUL
    b.size = 6;
    int has_slash = buffer_has_slash_suffix(&b);

    std::printf("digit:%d xdigit:%d slash:%d\n", d, x, has_slash);
    return 0;
}
