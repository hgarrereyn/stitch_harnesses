#include <iostream>
#include <fuse.h>

int main() {
    std::cout << "FUSE version " << FUSE_VERSION << " (" << FUSE_MAJOR_VERSION << "." << FUSE_MINOR_VERSION << ")\n";

    fuse_file_info fi{};
    fi.flags = 0;
    fi.direct_io = 1;
    fi.keep_cache = 0;
    fi.flush = 0;
    fi.fh = 1234;

    std::cout << "fh=" << (unsigned long long)fi.fh << ", direct_io=" << fi.direct_io << "\n";

    struct fuse_args args = FUSE_ARGS_INIT(0, nullptr);
    (void)args;

    return 0;
}
