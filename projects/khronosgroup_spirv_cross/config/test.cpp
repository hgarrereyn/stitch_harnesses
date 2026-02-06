#include <cstdio>
#include <spirv_cross/spirv_cross_c.h>

int main() {
    spvc_context context = nullptr;
    if (spvc_context_create(&context) != SPVC_SUCCESS) {
        return 1;
    }
    spvc_context_set_error_callback(context, nullptr, nullptr);
    spvc_context_release_allocations(context);
    spvc_context_destroy(context);
    puts("SPIRV-Cross C API ok");
    return 0;
}
