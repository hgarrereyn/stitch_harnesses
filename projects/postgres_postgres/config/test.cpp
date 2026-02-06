#include <stdio.h>
#include <libpq-fe.h>

int main() {
    int ver = PQlibVersion();
    int thread_safe = PQisthreadsafe();
    printf("libpq version: %d\n", ver);
    printf("thread safe: %s\n", thread_safe ? "yes" : "no");
    return 0;
}
