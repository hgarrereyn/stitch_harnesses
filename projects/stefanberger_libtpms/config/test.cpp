#include <cstdio>
#include <libtpms/tpm_library.h>
#include <libtpms/tpm_types.h>
#include <libtpms/tpm_error.h>

int main() {
    // Query version; this should not require initialization
    uint32_t ver = TPMLIB_GetVersion();
    std::printf("libtpms version: %u\n", ver);

    int prop = 0;
    TPMLIB_GetTPMProperty(TPMPROP_TPM_BUFFER_MAX, &prop);
    std::printf("TPM buffer max: %d\n", prop);

    return 0;
}
