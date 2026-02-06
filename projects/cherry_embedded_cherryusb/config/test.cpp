#include <cstdio>
#include "core/usbd_core.h"

static const uint8_t dummy_device_desc[] = { 0x12, 0x01, 0x00, 0x02, 0, 0, 0, 0x40, 0x34, 0x12, 0x78, 0x56, 0x00, 0x01, 1, 2, 3, 1 };

int main() {
    usbd_desc_register(0, dummy_device_desc);
    uint8_t state = usbd_get_ep0_next_state(0);
    bool configured = usb_device_is_configured(0);
    std::printf("state=%u configured=%d\n", state, configured ? 1 : 0);
    return 0;
}
