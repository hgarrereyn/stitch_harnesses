#include <cstdio>
#include <open62541/server.h>

int main() {
    UA_Server *server = UA_Server_new();
    if(!server) {
        std::printf("UA_Server_new failed\n");
        return 1;
    }

    UA_StatusCode st = UA_Server_run_startup(server);
    if(st != UA_STATUSCODE_GOOD) {
        std::printf("startup failed: %u\n", (unsigned)st);
        UA_Server_delete(server);
        return 1;
    }

    (void)UA_Server_run_iterate(server, UA_FALSE);

    st = UA_Server_run_shutdown(server);
    UA_Server_delete(server);

    std::printf("open62541 server lifecycle OK\n");
    return 0;
}
