#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
extern "C" {
#include <ssh_api.h>
}

int main() {
    struct ssh *s = nullptr;
    int r = ssh_init(&s, 0, nullptr); // client
    if (r != 0 || s == nullptr) {
        std::printf("ssh_init failed: %d\n", r);
        return 0;
    }
    // No network I/O: just exercise init/free paths
    ssh_free(s);
    std::printf("ssh_init/ssh_free succeeded\n");
    return 0;
}
