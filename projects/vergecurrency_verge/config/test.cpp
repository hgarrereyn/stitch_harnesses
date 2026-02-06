#include <cstdio>
#include <cstdint>
extern "C" {
#include <vergeconsensus.h>
}

int main() {
    unsigned int ver = vergeconsensus_version();
    printf("vergeconsensus version: %u\n", ver);

    const unsigned char scriptPubKey[] = {0x51}; // OP_1
    const unsigned char tx[] = {0x00}; // invalid tx blob
    vergeconsensus_error err;
    int ok = vergeconsensus_verify_script(scriptPubKey, sizeof(scriptPubKey), tx, sizeof(tx), 0, vergeconsensus_SCRIPT_FLAGS_VERIFY_NONE, &err);
    printf("verify result: %d, err: %d\n", ok, (int)err);
    return 0;
}
