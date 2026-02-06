#include <cstdio>
extern "C" {
#include <u8x8.h>
}

int main() {
    u8x8_t u8x8;
    u8x8_SetupStdio(&u8x8);
    u8x8_InitDisplay(&u8x8);

    // Select a built-in 8x8 font
    u8x8_SetFont(&u8x8, u8x8_font_chroma48medium8_r);

    // Draw some text and then show it when powering on
    u8x8_SetPowerSave(&u8x8, 1);
    u8x8_DrawString(&u8x8, 0, 0, "HI");
    u8x8_SetPowerSave(&u8x8, 0);
    return 0;
}
