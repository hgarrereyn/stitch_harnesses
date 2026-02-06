#include <glib.h>
extern "C" GQuark r_bundle_error_quark(void);

int main() {
    GQuark q = r_bundle_error_quark();
    g_message("rauc bundle error quark: %u", (unsigned)q);
    return 0;
}
