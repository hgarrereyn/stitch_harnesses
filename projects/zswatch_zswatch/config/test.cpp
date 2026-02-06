#include <cstdio>
#include <cstdint>
#include <cstring>

extern "C" {
#include "zsw_settings.h"
#include "zsw_cpu_freq.h"
#include "zsw_retained_ram_storage.h"
}

int main() {
    // Use types/macros from the library headers to ensure they compile
    zsw_settings_watchface_t wf{};
    wf.animations_on = true;
    wf.watchface_index = 3;
    wf.smooth_second_hand = false;
    wf.relative_battery = true;

    const char* path = ZSW_SETTINGS_PATH;
    const char* k_bri = ZSW_SETTINGS_KEY_BRIGHTNESS;

    struct retained_data rd{};
    rd.boots = 1;
    std::snprintf(rd.timezone, sizeof(rd.timezone), "UTC");

    zsw_cpu_freq_t f = ZSW_CPU_FREQ_DEFAULT;

    std::printf("ok:%s/%s wf_idx=%u boots=%u f=%d\n", path, k_bri, wf.watchface_index, rd.boots, (int)f);
    return 0;
}
