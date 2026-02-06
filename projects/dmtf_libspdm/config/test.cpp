#include <cstdio>
extern "C" {
#include "library/spdm_common_lib.h"
}
int main(){
    std::printf("libspdm headers present: version %u.%u.%u\n", LIBSPDM_MAJOR_VERSION, LIBSPDM_MINOR_VERSION, LIBSPDM_PATCH_VERSION);
    return 0;
}
