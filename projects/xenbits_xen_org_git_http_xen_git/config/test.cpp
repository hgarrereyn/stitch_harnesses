#include <stdio.h>
#include <stdbool.h>
extern "C" {
#include <xenstore.h>
}

int main() {
    const char *sock = xs_daemon_socket();
    const char *rundir = xs_daemon_rundir();
    bool sub = xs_path_is_subpath("/local/domain", "/local/domain/0");

    printf("xs_daemon_socket: %s\n", sock ? sock : "(null)");
    printf("xs_daemon_rundir: %s\n", rundir ? rundir : "(null)");
    printf("is_subpath: %s\n", sub ? "true" : "false");
    return 0;
}
