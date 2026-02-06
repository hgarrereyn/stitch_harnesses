#include <valkey/valkey.h>
#include <cstdio>
#include <cstring>

int main() {
    // Use the reply parser without any networking
    valkeyReader *r = valkeyReaderCreate();
    if (!r) return 1;

    const char *resp = "+OK\r\n"; // simple status reply
    if (valkeyReaderFeed(r, resp, (int)strlen(resp)) != VALKEY_OK) {
        valkeyReaderFree(r);
        return 1;
    }

    void *reply = nullptr;
    if (valkeyReaderGetReply(r, &reply) != VALKEY_OK || reply == nullptr) {
        valkeyReaderFree(r);
        return 1;
    }

    valkeyReply *rep = (valkeyReply*)reply;
    // Print parsed reply type and content
    printf("Reply type=%d, str=%s\n", rep->type, rep->str ? rep->str : "");

    freeReplyObject(reply);
    valkeyReaderFree(r);
    return 0;
}
