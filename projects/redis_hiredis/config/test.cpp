#include <cstdio>
extern "C" {
#include <hiredis/hiredis.h>
#include <hiredis/read.h>
}

int main() {
    // Use the reply parser API so this runs without a Redis server
    redisReader *reader = redisReaderCreate();
    if (!reader) {
        std::printf("Failed to create redisReader\n");
        return 1;
    }

    const char *msg = "+OK\r\n"; // RESP2 simple status reply
    if (redisReaderFeed(reader, msg, 5) != REDIS_OK) {
        std::printf("redisReaderFeed failed\n");
        redisReaderFree(reader);
        return 1;
    }

    void *vreply = nullptr;
    if (redisReaderGetReply(reader, &vreply) != REDIS_OK) {
        std::printf("redisReaderGetReply failed\n");
        redisReaderFree(reader);
        return 1;
    }

    redisReply *reply = static_cast<redisReply*>(vreply);
    if (reply && reply->type == REDIS_REPLY_STATUS && reply->str) {
        std::printf("Parsed status reply: %s\n", reply->str);
    } else {
        std::printf("Unexpected reply type\n");
    }

    if (reply) freeReplyObject(reply);
    redisReaderFree(reader);
    return 0;
}
