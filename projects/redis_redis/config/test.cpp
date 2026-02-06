#include <iostream>
#include <cstring>
#include <hiredis/hiredis.h>
#include <hiredis/read.h>

int main() {
    // Format a simple command
    char *cmd = nullptr;
    int rc = redisFormatCommand(&cmd, "PING");
    if (rc == -1 || cmd == nullptr) {
        std::cout << "Failed to format command" << std::endl;
        return 1;
    }
    // Simulate a server response and parse it
    const char *resp = "+PONG\r\n";
    redisReader *reader = redisReaderCreate();
    if (!reader) {
        std::cout << "Failed to create reader" << std::endl;
        redisFreeCommand(cmd);
        return 1;
    }
    redisReaderFeed(reader, resp, strlen(resp));
    void *reply = nullptr;
    if (redisReaderGetReply(reader, &reply) == REDIS_OK && reply) {
        redisReply *r = (redisReply*)reply;
        std::cout << "Parsed reply type: " << r->type << " text: " << (r->str ? r->str : "") << std::endl;
        freeReplyObject(reply);
    } else {
        std::cout << "Failed to parse reply" << std::endl;
    }
    redisReaderFree(reader);
    redisFreeCommand(cmd);
    return 0;
}
