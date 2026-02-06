#include <cstdio>
#include <cstdint>
#include <alignment.h>
#include <align_asset_macro.h>

// Use some of the public macros as a simple smoke test
struct ALIGN_ASSET(16) AlignedStruct { uint8_t bytes[16]; };

int main() {
    uint32_t v = 37;
    uint32_t a8 = ALIGN8(v);
    uint32_t a16 = ALIGN16(v);
    uint32_t a32 = ALIGN32(v);
    AlignedStruct s{};
    // Just print to ensure code runs
    std::printf("%u %u %u %zu\n", a8, a16, a32, sizeof(s));
    return 0;
}
