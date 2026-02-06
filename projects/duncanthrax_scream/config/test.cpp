#include <cstdio>
#include <cstdint>
extern "C" {
#include <scream.h>
#include <raw.h>
}

int verbosity = 0; // required by raw.c

int main() {
    // Initialize raw output (writes audio frames to stdout)
    if (raw_output_init() != 0) {
        return 1;
    }

    // Prepare a tiny dummy audio frame (silence)
    unsigned char dummy[8] = {0};
    receiver_data_t data;
    data.format.sample_rate = 129; // 44.1kHz base, multiplier 1
    data.format.sample_size = 16;  // 16-bit samples
    data.format.channels = 2;      // stereo
    data.format.channel_map = 0x0003; // FL | FR
    data.audio_size = sizeof(dummy);
    data.audio = dummy;

    // Send once
    if (raw_output_send(&data) != 0) {
        return 1;
    }

    // Success
    std::puts("ok");
    return 0;
}
