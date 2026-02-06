#include <cstdio>
#include <cstdint>
#include <IRVersion.h>
#include <IRProtocol.h>

int main() {
    // Print library version defined by IRVersion.h
    std::printf("IRremote version: %s (hex %06x)\n", VERSION_IRREMOTE, (unsigned)VERSION_IRREMOTE_HEX);

    // Use some API types from IRProtocol.h
    decode_type_t proto = NEC; // one of the supported protocols
    std::printf("Example protocol enum value (NEC) = %d\n", (int)proto);

    // Use one of the constants from IRProtocol.h
    std::printf("NEC carrier frequency nominal: %d kHz\n", (int)NEC_KHZ);

    // Exercise DistanceWidthTimingInfoStruct
    DistanceWidthTimingInfoStruct t {8900, 4450, 560, 1690, 560, 560};
    uint32_t checksum = (uint32_t)t.HeaderMarkMicros + t.HeaderSpaceMicros + t.OneMarkMicros + t.OneSpaceMicros + t.ZeroMarkMicros + t.ZeroSpaceMicros;
    std::printf("Timing checksum: %u\n", checksum);

    return 0;
}
