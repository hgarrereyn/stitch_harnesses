#include <stdio.h>
#include "miniaudio/miniaudio.h"

int main() {
    ma_context_config cfg = ma_context_config_init();
    ma_uint32 bps = ma_get_bytes_per_sample(ma_format_s16);
    printf("miniaudio ready. threadPriority=%d, bytesPerSample(s16)=%u\n", (int)cfg.threadPriority, (unsigned)bps);
    return 0;
}
