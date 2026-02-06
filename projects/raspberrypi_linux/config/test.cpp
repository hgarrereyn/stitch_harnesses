#include <cstdio>
#include <cstdint>
extern "C" {
#include "libfdt.h"
}

int main() {
    unsigned char buf[4096];
    if (fdt_create(buf, sizeof(buf)) != 0) return 1;
    if (fdt_finish_reservemap(buf) != 0) return 1;
    if (fdt_begin_node(buf, "") != 0) return 1; // root node
    const char compat[] = "test,device"; // NUL-terminated
    if (fdt_property(buf, "compatible", compat, sizeof(compat)) != 0) return 1;
    if (fdt_end_node(buf) != 0) return 1;
    if (fdt_finish(buf) != 0) return 1;
    if (fdt_check_header(buf) != 0) return 1;
    std::printf("DTB size: %u\n", fdt_totalsize(buf));
    return 0;
}
