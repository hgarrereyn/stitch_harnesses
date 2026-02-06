#include <cstdio>
#include <libssh/libssh.h>

int main() {
    const char* ver = ssh_version(0);
    if (ver) {
        std::printf("libssh version: %s\n", ver);
    } else {
        std::printf("libssh version unavailable\n");
    }

    ssh_session session = ssh_new();
    if (!session) {
        std::printf("Failed to create ssh session\n");
        return 0;
    }

    // Set a few simple options without connecting
    ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
    ssh_options_set(session, SSH_OPTIONS_PORT_STR, "22");

    ssh_free(session);
    std::printf("libssh basic API test completed.\n");
    return 0;
}
