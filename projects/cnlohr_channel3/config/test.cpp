#include <stdio.h>
#include <stdint.h>
#include <CbTable.h>
#include <broadcast_tables.h>

int main() {
    // Touch a few symbols to ensure linking works
    uint32_t sum = 0;
    // PREMOD_ENTRIES and PREMOD_SIZE should be defined
    for (int i = 0; i < PREMOD_ENTRIES * PREMOD_SIZE; i += PREMOD_SIZE) {
        sum ^= premodulated_table[i];
    }
    // Use CbLookup for both PAL and NTSC sizes conditionally
#ifdef PAL
    int lines = (int)(sizeof(CbLookupPAL)/sizeof(CbLookupPAL[0]));
    sum ^= lines;
#else
    int lines = (int)(sizeof(CbLookupNTSC)/sizeof(CbLookupNTSC[0]));
    sum ^= lines;
#endif
    printf("channel3 table lib ok: %u\n", (unsigned)sum);
    return 0;
}
