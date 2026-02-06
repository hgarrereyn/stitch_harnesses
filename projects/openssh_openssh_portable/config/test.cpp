#include <cstdio>
extern "C" {
#include <ssh_api.h>
}

int main() {
    struct ssh *ctx = nullptr;
    if (ssh_init(&ctx, 0, nullptr) != 0 || ctx == nullptr) {
        std::puts("ssh_init failed");
        return 1;
    }
    // Immediately free without doing any network I/O
    ssh_free(ctx);
    std::puts("ssh_init/ssh_free ok");
    return 0;
}
