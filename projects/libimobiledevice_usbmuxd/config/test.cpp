extern "C" {
#include <usbmuxd/log.h>
}

int main() {
    log_enable_syslog();
    usbmuxd_log(LL_INFO, "usbmuxd internal logging test %d", 42);
    log_disable_syslog();
    return 0;
}
