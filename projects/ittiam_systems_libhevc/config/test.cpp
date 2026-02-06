#include <cstdio>
#include <cstring>
extern "C" {
#include "/fuzz/install/include/ihevc_typedefs.h"
#include "/fuzz/install/include/iv.h"
}

// The decoder exports this symbol from decoder/ihevcd_api.c
extern "C" IV_API_CALL_STATUS_T ihevcd_get_version(CHAR *pc_version_string, UWORD32 u4_version_buffer_size);

int main() {
    CHAR ver[128];
    memset(ver, 0, sizeof(ver));
    IV_API_CALL_STATUS_T st = ihevcd_get_version(ver, (UWORD32)sizeof(ver));
    (void)st;
    std::printf("libhevc decoder version: %s\n", ver);
    return 0;
}
