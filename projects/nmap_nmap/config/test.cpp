#include <cstdio>
#include <nsock.h>

int main() {
    nsock_pool pool = nsock_pool_new(nullptr);
    if (!pool) {
        std::printf("Failed to create nsock pool\n");
        return 1;
    }

    nsock_set_loglevel(NSOCK_LOG_NONE);
    nsock_pool_set_udata(pool, (void*)0x1234);
    void* u = nsock_pool_get_udata(pool);
    std::printf("nsock pool udata: %p\n", u);

    (void)nsock_loop(pool, 0);

    nsock_pool_delete(pool);
    std::printf("nsock basic test OK\n");
    return 0;
}
