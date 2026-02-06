#include <iostream>
extern "C" {
#include "/fuzz/src/src/libcrun/error.h"
#include "/fuzz/src/src/libcrun/container.h"
}

int main() {
    // Set verbosity and exercise a couple of small API calls
    libcrun_set_verbosity(LIBCRUN_VERBOSITY_DEBUG);

    libcrun_error_t err = nullptr;
    // Create and immediately release an error object
    libcrun_make_error(&err, 0, "hello %s", "world");
    if (err) {
        libcrun_error_release(&err);
    }

    // Touch the context type to ensure headers parse fine
    libcrun_context_t ctx{};
    ctx.id = "dummy";

    std::cout << "libcrun basic test OK\n";
    return 0;
}
