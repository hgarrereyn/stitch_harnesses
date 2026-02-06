#include <stdio.h>
#include <string.h>
#include <stdint.h>
extern "C" {
#include "/fuzz/install/include/eth.h"
}

int main() {
    struct eth_addr mac = {0};
    const char *s = "aa:bb:cc:dd:ee:ff";
    char buf[64] = {0};

    if (eth_addr_init(&mac, s) != 0) {
        printf("eth_addr_init failed\n");
        return 1;
    }
    eth_addr_to_str(&mac, buf);
    printf("MAC: %s\n", buf);
    return 0;
}
