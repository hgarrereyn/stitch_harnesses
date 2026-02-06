#include <cstdio>
#include <cstdint>
#include <idevicerestore.h>

static void progress_cb(int step, double step_progress, void* userdata) {
    (void)userdata;
    printf("progress: step=%d progress=%.2f\n", step, step_progress);
}

int main() {
    struct idevicerestore_client_t* client = idevicerestore_client_new();
    if (!client) {
        printf("failed to create client\n");
        return 0;
    }
    idevicerestore_set_flags(client, FLAG_NOACTION | FLAG_DEBUG);
    idevicerestore_set_progress_callback(client, progress_cb, nullptr);
    const char* comp = get_component_name("Firmware/all_flash/manifest.plist");
    printf("component name: %s\n", comp ? comp : "(none)");
    const char* err = idevicerestore_get_error();
    printf("last error: %s\n", err ? err : "(none)");
    idevicerestore_client_free(client);
    return 0;
}
