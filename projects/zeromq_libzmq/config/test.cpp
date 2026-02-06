#include <cstdio>
#include <cstring>
#include <zmq.h>

int main() {
    void* ctx = zmq_ctx_new();
    if(!ctx) { std::fprintf(stderr, "ctx new failed\n"); return 1; }

    void* s1 = zmq_socket(ctx, ZMQ_PAIR);
    void* s2 = zmq_socket(ctx, ZMQ_PAIR);
    if(!s1 || !s2) { std::fprintf(stderr, "socket failed\n"); return 1; }

    int rc = zmq_bind(s1, "inproc://test");
    if(rc != 0) { std::fprintf(stderr, "bind failed: %s\n", zmq_strerror(zmq_errno())); return 1; }

    rc = zmq_connect(s2, "inproc://test");
    if(rc != 0) { std::fprintf(stderr, "connect failed: %s\n", zmq_strerror(zmq_errno())); return 1; }

    const char* msg = "hello";
    rc = zmq_send(s2, msg, std::strlen(msg), 0);
    if(rc < 0) { std::fprintf(stderr, "send failed: %s\n", zmq_strerror(zmq_errno())); return 1; }

    char buf[16] = {0};
    rc = zmq_recv(s1, buf, sizeof(buf), 0);
    if(rc < 0) { std::fprintf(stderr, "recv failed: %s\n", zmq_strerror(zmq_errno())); return 1; }

    std::printf("Received: %.*s\n", rc, buf);

    zmq_close(s1);
    zmq_close(s2);
    zmq_ctx_term(ctx);
    return 0;
}
