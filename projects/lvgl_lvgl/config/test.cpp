#include <stdio.h>
#include <lvgl/lvgl.h>
#include <lvgl/lv_version.h>

int main() {
    lv_init();
    printf("LVGL initialized. Version %d.%d.%d\n", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
    return 0;
}
