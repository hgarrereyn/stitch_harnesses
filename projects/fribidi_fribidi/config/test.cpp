#include <cstdio>
#include <cstdint>
#include <fribidi/fribidi.h>

int main() {
    // Simple UTF-32 string: "ABC \xD7\x90" (ALEF in Hebrew)
    FriBidiChar input[] = { 'A', 'B', 'C', 0x05D0, 0 }; // Null-terminated, but we pass explicit len
    FriBidiStrIndex len = 4;

    FriBidiCharType base_dir = FRIBIDI_TYPE_ON; // Let fribidi determine base direction

    FriBidiChar visual[8] = {0};
    FriBidiStrIndex l2v[8] = {0};
    FriBidiStrIndex v2l[8] = {0};
    FriBidiLevel levels[8] = {0};

    fribidi_boolean ok = fribidi_log2vis(
        input, len, &base_dir, visual, l2v, v2l, levels);

    if (!ok) {
        std::printf("fribidi_log2vis failed\n");
        return 1;
    }

    // Print base direction and first visual codepoint
    std::printf("base_dir=%d first_visual=%u\n", (int)base_dir, (unsigned)visual[0]);
    return 0;
}
