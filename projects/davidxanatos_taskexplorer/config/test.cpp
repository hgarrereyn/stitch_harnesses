#include <cstdio>
#include <cstring>
#include "TaskExplorer/Common/SVariant.h"

int main() {
    // Create a simple UINT32 variant, serialize, deserialize, and verify
    VARIANT v;
    uint32 val = 123456789u;
    Variant_FromUInt32(val, &v);

    unsigned char buffer[32];
    size_t written = Variant_ToBuffer(&v, buffer, sizeof(buffer));
    if (written == 0) return 1;

    VARIANT parsed;
    size_t read = Variant_FromBuffer(buffer, written, &parsed);
    if (read == 0) return 2;

    uint32 out = 0;
    if (!Variant_ToInt(&parsed, &out, sizeof(out))) return 3;

    if (out != val) return 4;

    std::printf("ok %u\n", out);
    return 0;
}
