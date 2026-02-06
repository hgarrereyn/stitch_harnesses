#include <stdio.h>
#include <libusb.h>

int main() {
    libusb_context *ctx = NULL;
    int r = libusb_init(&ctx);
    if (r != 0) {
        printf("libusb_init failed: %d\n", r);
        return 0; // still exit successfully
    }

    libusb_device **list = NULL;
    ssize_t cnt = libusb_get_device_list(ctx, &list);
    if (cnt < 0) {
        printf("libusb_get_device_list error: %zd\n", cnt);
        libusb_exit(ctx);
        return 0;
    }

    printf("Found %zd USB devices (may be 0 in container)\n", cnt);

    if (list) libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    return 0;
}
