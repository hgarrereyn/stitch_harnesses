#include <iostream>
#include <unbound.h>

int main() {
    const char* ver = ub_version();
    if(!ver) {
        std::cout << "libunbound version not available" << std::endl;
        return 1;
    }
    std::cout << "libunbound version: " << ver << std::endl;

    ub_ctx* ctx = ub_ctx_create();
    if(!ctx) {
        std::cout << "Failed to create ub_ctx" << std::endl;
        return 1;
    }
    int err = ub_ctx_set_option(ctx, "verbosity:", "0");
    if(err != 0) {
        std::cout << "ub_ctx_set_option failed: " << ub_strerror(err) << std::endl;
    }
    ub_ctx_delete(ctx);
    return 0;
}
