#include <iostream>
#include <memory>
#include "hf3fs.h"

int main() {
    using namespace hf3fs::lib;
    std::cout << "HF3FS_SUPER_MAGIC=" << std::hex << HF3FS_SUPER_MAGIC << std::dec << "\n";

    // Construct a successful Result value
    Result<int> r = Result<int>(42);
    if (r) {
        std::cout << "Result value: " << r.value() << "\n";
    }

    // Create and free an iovec structure (not using library allocation to avoid external deps)
    iovec v{}; v.iov_base = nullptr; v.iov_len = 0; v.user_data = nullptr;
    (void)v;

    return 0;
}
