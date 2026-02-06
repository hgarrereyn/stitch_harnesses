#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
extern "C" {
#include "socket.h"
}

// Define global variables expected by the library
extern "C" {
int debug_level = 1;
int ipver = SOCK_IPV4;
int reuseaddr = 0;
int reuseport = 0;
int opt_debug = 0;
struct sockaddr_in remote;
}

int main() {
    // Create a UDP socket address for localhost:0 (ephemeral) without connecting
    socket_t *s = sock_create((char*)"127.0.0.1", (char*)"0", SOCK_IPV4, SOCK_TYPE_UDP, 1, 0);
    if (!s) {
        printf("sock_create failed\n");
        return 1;
    }

    char buf[ADDRSTRLEN] = {0};
    if (sock_get_addrstr(s, buf, sizeof(buf))) {
        printf("Socket address: %s\n", buf);
    } else {
        printf("Failed to get socket address string\n");
    }

    sock_free(s);
    printf("OK\n");
    return 0;
}
