#include <cstdio>
#include "yojimbo.h"
#include "yojimbo_address.h"

int main() {
    if (!InitializeYojimbo()) {
        printf("InitializeYojimbo failed\n");
        return 0; // still exit
    }
    yojimbo::Address addr("127.0.0.1:40000");
    char buffer[256];
    const char * s = addr.ToString(buffer, sizeof(buffer));
    if (s) {
        printf("Address: %s\n", s);
    }
    EnablePacketTagging();
    ShutdownYojimbo();
    return 0;
}
