#include <ggwave/ggwave.h>
#include <cstdio>
#include <cstring>
#include <vector>

int main() {
    // Get default parameters and create an instance that can TX and RX
    ggwave_Parameters params = ggwave_getDefaultParameters();
    params.operatingMode = GGWAVE_OPERATING_MODE_RX_AND_TX;

    ggwave_Instance inst = ggwave_init(params);
    if (inst < 0) {
        std::printf("Failed to init ggwave\n");
        return 1;
    }

    const char *msg = "Hello, ggwave!";

    // Query required waveform size in bytes
    int nbytes = ggwave_encode(inst, msg, (int)std::strlen(msg), GGWAVE_PROTOCOL_DT_FAST, 25, nullptr, 1);
    if (nbytes <= 0) {
        std::printf("encode query failed\n");
        ggwave_free(inst);
        return 1;
    }

    std::vector<unsigned char> waveform(nbytes);

    // Generate waveform
    int gen = ggwave_encode(inst, msg, (int)std::strlen(msg), GGWAVE_PROTOCOL_DT_FAST, 25, waveform.data(), 0);
    if (gen <= 0) {
        std::printf("encode failed\n");
        ggwave_free(inst);
        return 1;
    }

    // Decode the generated waveform
    char payload[256];
    int decoded = ggwave_decode(inst, waveform.data(), gen, payload);
    if (decoded > 0 && decoded < (int)sizeof(payload)) {
        payload[decoded] = '\0';
        std::printf("Decoded: %s\n", payload);
    } else if (decoded == 0) {
        std::printf("No payload decoded\n");
    } else {
        std::printf("Decode error: %d\n", decoded);
    }

    ggwave_free(inst);
    return 0;
}
