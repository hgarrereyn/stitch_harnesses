#include <libudev.h>
#include <cstdio>

int main() {
    struct udev* u = udev_new();
    if (!u) {
        std::printf("udev_new failed\n");
        return 0;
    }
    std::printf("libudev context created successfully\n");
    udev_unref(u);
    return 0;
}
