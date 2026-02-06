#include <iostream>
#include <pthread.h>
#include <string.h>
#include "rpc.h"

int main() {
    conn_t conn{}; // zero-initialize

    // Initialize sync primitives used by the RPC helpers
    pthread_mutex_init(&conn.read_mutex, nullptr);
    pthread_mutex_init(&conn.write_mutex, nullptr);
    pthread_cond_init(&conn.read_cond, nullptr);

    // Start a dummy request and attempt to send some bytes
    if (rpc_write_start_request(&conn, 42) != 0) {
        std::cerr << "rpc_write_start_request failed" << std::endl;
        return 1;
    }

    const char msg[] = "hi";
    rpc_write(&conn, msg, sizeof(msg));
    int req_id = rpc_write_end(&conn);

    std::cout << "Request ID: " << req_id << " (expected -1 if write failed)" << std::endl;

    // Clean up
    pthread_mutex_destroy(&conn.read_mutex);
    pthread_mutex_destroy(&conn.write_mutex);
    pthread_cond_destroy(&conn.read_cond);

    return 0;
}
