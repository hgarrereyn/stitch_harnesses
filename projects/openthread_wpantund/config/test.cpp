#include <iostream>
#include <wpantund/wpan-error.h>
#include <wpantund/wpan-properties.h>
#include <wpantund/wpan-dbus-v1.h>

int main() {
    // Use a few constants from the public headers to ensure they are available
    int status_ok = kWPANTUNDStatus_Ok; // from wpan-error.h (enum only, no linking needed)
    const char* prop_name = kWPANTUNDProperty_ConfigNCPDriverName; // from wpan-properties.h
    const char* dbus_if = WPANTUND_DBUS_APIv1_INTERFACE; // from wpan-dbus-v1.h

    std::cout << "wpantund headers accessible. status_ok=" << status_ok
              << ", prop_name=" << prop_name
              << ", dbus_if=" << dbus_if << std::endl;
    return 0;
}
