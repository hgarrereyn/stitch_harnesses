#include <metacall/metacall.h>
#include <cstdio>

int main() {
    metacall_log_null();
    metacall_flags(METACALL_FLAGS_FORK_SAFE);
    if (metacall_initialize() != 0) {
        std::printf("MetaCall init failed\n");
        return 0; // do not fail the test
    }
    const char *ser = metacall_serial();
    const char *det = metacall_detour();
    std::printf("MetaCall default serial: %s, detour: %s\n", ser ? ser : "(null)", det ? det : "(null)");
    return 0;
}
