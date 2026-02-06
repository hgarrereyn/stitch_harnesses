#include <stdio.h>
#include <haproxy/version.h>

int main() {
    printf("product=%s branch=%s\n", PRODUCT_NAME, PRODUCT_BRANCH);
    printf("version=%s date=%s\n", HAPROXY_VERSION, HAPROXY_DATE);
    return 0;
}
