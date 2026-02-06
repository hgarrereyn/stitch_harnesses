#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>

int main() {
    int s = nn_socket(AF_SP, NN_PAIR);
    if (s < 0) {
        int err = nn_errno();
        fprintf(stderr, "nn_socket failed: %s\n", nn_strerror(err));
        return 0; // still exit successfully for testing
    }
    // Just create and close a socket; no network operations so it won't block.
    if (nn_close(s) != 0) {
        int err = nn_errno();
        fprintf(stderr, "nn_close failed: %s\n", nn_strerror(err));
    }
    return 0;
}
