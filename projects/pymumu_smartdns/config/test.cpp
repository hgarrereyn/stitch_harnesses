#include <stdio.h>
#include <smartdns/smartdns.h>

int main() {
    const char *ver = smartdns_version();
    if (!ver) ver = "unknown";
    printf("smartdns version: %s\n", ver);
    return 0;
}
