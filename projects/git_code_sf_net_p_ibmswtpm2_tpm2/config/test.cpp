#include <stdio.h>
#include <stdint.h>
extern "C" int verbose = 0; // satisfy references in some modules
extern "C" {
#include "tpm_public.h"
#include "Manufacture_fp.h"
#include "_TPM_Init_fp.h"
#include "Startup_fp.h"
#include "GetRandom_fp.h"
#include "platform_public_interface.h"
#include "tpm_to_platform_interface.h"
}

int main() {
    // Bring up NV and manufacture if needed
    if (_plat__NVEnable(NULL, 0) < 0) {
        printf("NV enable failed\n");
        return 1;
    }
    if (_plat__NVNeedsManufacture()) {
        if (TPM_Manufacture(MANUF_FIRST_TIME) != 0) {
            printf("TPM_Manufacture failed\n");
            return 1;
        }
    }
    _plat__NVDisable((void*)0, 0);

    // Power on and make NV available within the simulator
    _plat__Signal_PowerOn();
    _plat__SetNvAvail();

    // TPM2_Startup(CLEAR)
    Startup_In sin; sin.startupType = TPM_SU_CLEAR;
    TPM_RC src = TPM2_Startup(&sin);
    if (src != 0) {
        printf("TPM2_Startup failed: 0x%x\n", src);
        return 1;
    }

    // GetRandom(8)
    GetRandom_In rin; rin.bytesRequested = 8;
    GetRandom_Out rout; 
    TPM_RC grc = TPM2_GetRandom(&rin, &rout);
    if (grc != 0) {
        printf("TPM2_GetRandom failed: 0x%x\n", grc);
        return 1;
    }
    printf("Got %u random bytes from TPM simulator.\n", rout.randomBytes.t.size);
    return 0;
}
