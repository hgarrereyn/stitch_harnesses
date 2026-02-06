#include <cstdio>
#include <cstring>
extern "C" {
#include <njs.h>
}

int main() {
    njs_vm_opt_t opts;
    njs_vm_opt_init(&opts);
    opts.backtrace = 1;

    njs_vm_t* vm = njs_vm_create(&opts);
    if (!vm) {
        std::printf("Failed to create njs VM\n");
        return 1;
    }

    const char* script = "1+2";
    unsigned char* start = (unsigned char*)script;
    unsigned char* end = (unsigned char*)script + std::strlen(script);

    if (njs_vm_compile(vm, &start, end) != 0) {
        std::printf("Compile error\n");
        njs_vm_destroy(vm);
        return 1;
    }

    njs_opaque_value_t result;
    if (njs_vm_start(vm, (njs_value_t*)&result) != 0) {
        std::printf("Execution error\n");
        njs_vm_destroy(vm);
        return 1;
    }

    if (njs_value_is_number((njs_value_t*)&result)) {
        double val = njs_value_number((njs_value_t*)&result);
        std::printf("njs evaluated 1+2 = %.0f\n", val);
    } else {
        std::printf("Unexpected result type\n");
    }

    njs_vm_destroy(vm);
    return 0;
}
