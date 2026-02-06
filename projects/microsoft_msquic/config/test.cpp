#include <msquic.h>
#include <stdio.h>

int main() {
    const void* api = nullptr;
    QUIC_STATUS status = MsQuicOpenVersion(QUIC_API_VERSION_2, &api);
    if (QUIC_FAILED(status)) {
        printf("MsQuicOpenVersion failed: %u\n", (unsigned)status);
        return 0; // don't fail
    }
    MsQuicClose(api);
    printf("MsQuic open/close ok\n");
    return 0;
}
