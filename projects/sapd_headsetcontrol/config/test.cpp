#include <stdio.h>
#include <stdlib.h>
#include <headsetcontrol/headsetcontrol_c.h>

int main() {
    printf("HeadsetControl C API version: %s\n", hsc_version());

    // Enable test device so we can discover something even without hardware
    hsc_enable_test_device(true);

    hsc_headset_t* headsets = NULL;
    int count = hsc_discover(&headsets);
    if (count < 0) {
        printf("Discover error: %d\n", count);
        return 0;
    }

    printf("Discovered %d headset(s)\n", count);
    for (int i = 0; i < count; i++) {
        const char* name = hsc_get_name(headsets[i]);
        printf(" - %s (vid=0x%04x pid=0x%04x)\n", name ? name : "(unknown)",
               (unsigned)hsc_get_vendor_id(headsets[i]), (unsigned)hsc_get_product_id(headsets[i]));
    }

    hsc_free_headsets(headsets, count);

    // Show number of supported devices known by the library
    int supported = hsc_supported_device_count();
    printf("Supported device definitions: %d\n", supported);
    if (supported > 0) {
        const char* first = hsc_supported_device_name(0);
        if (first) printf("Example supported device: %s\n", first);
    }

    return 0;
}
