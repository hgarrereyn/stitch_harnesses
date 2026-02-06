#include <cstdio>
#include <cstring>
#include <mdbtools.h>

int main() {
    const char* ver = mdb_get_version();
    if (!ver) {
        printf("mdb_get_version returned null\n");
        return 1;
    }
    printf("MDB Tools version: %s\n", ver);
    // Light touch of API: verify string length and print first char
    size_t len = std::strlen(ver);
    printf("Version length: %zu, first char: %c\n", len, ver[0]);
    return 0;
}
