#include <cstdio>
extern "C" {
#include <dislocker/dislocker.h>
}

int main() {
    dis_context_t ctx = dis_new();
    if (!ctx) {
        std::printf("dis_new failed\n");
        return 0;
    }
    int fd = get_fvevol_fd(ctx);
    std::printf("get_fvevol_fd returned %d\n", fd);
    (void)dis_destroy(ctx);
    return 0;
}
