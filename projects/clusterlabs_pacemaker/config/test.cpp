#include <stdio.h>
#include <crm/common/logging.h>

int main() {
    crm_log_preinit("fuzz-test", 0, NULL);
    do_crm_log(LOG_STDOUT, "pacemaker log test: %s %d", "ok", 42);
    printf("basic pacemaker headers usable\n");
    return 0;
}
