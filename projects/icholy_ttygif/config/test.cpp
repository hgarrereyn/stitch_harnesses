#include <cstdio>
#include <cstddef>
extern "C" {
#include "string_builder.h"
}

int main() {
    StringBuilder *sb = StringBuilder_new();
    StringBuilder_write(sb, "Hello, ");
    StringBuilder_write(sb, "ttygif library!\n");
    std::fputs(StringBuilder_str(sb), stdout);
    StringBuilder_free(sb);
    return 0;
}
