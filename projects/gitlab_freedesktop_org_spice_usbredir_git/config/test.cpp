#include <cstdio>
#include <cstdint>
#include "usbredirparser.h"

static void log_cb(void *priv, int level, const char *msg) {
    (void)priv; (void)level; (void)msg;
}
static int read_cb(void *priv, uint8_t *data, int count) {
    (void)priv; (void)data; (void)count; return 0; // non-blocking, no data
}
static int write_cb(void *priv, uint8_t *data, int count) {
    (void)priv; (void)data; return count; // accept all data
}

int main() {
    // Create parser
    usbredirparser *p = usbredirparser_create();
    if (!p) { std::printf("create failed\n"); return 0; }
    p->priv = nullptr;
    p->log_func = log_cb;
    p->read_func = read_cb;
    p->write_func = write_cb;

    // Initialize capabilities
    uint32_t caps[USB_REDIR_CAPS_SIZE] = {0};
    usbredirparser_caps_set_cap(caps, usb_redir_cap_64bits_ids);

    usbredirparser_init(p, "test", caps, USB_REDIR_CAPS_SIZE, 0);

    // Exercise a couple of trivial calls
    (void)usbredirparser_have_cap(p, usb_redir_cap_64bits_ids);
    (void)usbredirparser_has_data_to_write(p);
    (void)usbredirparser_do_write(p);

    usbredirparser_destroy(p);
    return 0;
}
