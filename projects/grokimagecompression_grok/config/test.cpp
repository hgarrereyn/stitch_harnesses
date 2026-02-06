#include <cstdio>
#include <cstdint>
extern "C" {
#include <grok.h>
}

int main() {
    grk_cparameters params{}; // zero-initialize
    grk_compress_set_default_params(&params);
    std::printf("Grok defaults: numresolution=%u, cblock=%ux%u\n",
                (unsigned)params.numresolution,
                (unsigned)params.cblockw_init,
                (unsigned)params.cblockh_init);
    return 0;
}
