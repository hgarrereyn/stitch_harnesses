#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
#include <waveshare/Config/DEV_Config.h>
#include <waveshare/e-Paper/EPD_2in9.h>
}

int main() {
    if (DEV_Module_Init() != 0) {
        printf("DEV_Module_Init failed (expected on non-target env)\n");
    }
    const int width = EPD_2IN9_WIDTH;
    const int height = EPD_2IN9_HEIGHT;
    size_t buf_size = (size_t)width * (size_t)height / 8;
    unsigned char *img = (unsigned char*)malloc(buf_size);
    if (!img) return 0;
    memset(img, 0xFF, buf_size);

    EPD_2IN9_Init(EPD_2IN9_FULL);
    EPD_2IN9_Clear();
    EPD_2IN9_Display(img);
    EPD_2IN9_Sleep();

    free(img);
    DEV_Module_Exit();
    printf("waveshare e-paper static library linked and ran basic calls.\n");
    return 0;
}
