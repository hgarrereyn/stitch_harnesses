#include <stdio.h>
#include <string.h>
#include <bluetooth/bluetooth.h>

int main() {
    const char *addr_str = "01:23:45:67:89:AB";
    bdaddr_t addr = {0};
    if (str2ba(addr_str, &addr) < 0) {
        printf("str2ba failed\n");
        return 1;
    }
    char out[18] = {0};
    ba2str(&addr, out);
    printf("Parsed and formatted address: %s -> %s\n", addr_str, out);
    // Check that conversion preserved value
    if (strcmp(addr_str, out) != 0) {
        printf("Mismatch in address conversion!\n");
        return 1;
    }
    return 0;
}
