#include <cstdio>
extern "C" {
#include "sopc_version.h"
#include "sopc_buffer.h"
}

int main() {
    SOPC_Buffer* b = SOPC_Buffer_Create(16);
    if (nullptr == b) {
        return 1;
    }
    SOPC_Buffer_Delete(b);
    std::printf("S2OPC version: %s\n", SOPC_TOOLKIT_VERSION);
    return 0;
}
