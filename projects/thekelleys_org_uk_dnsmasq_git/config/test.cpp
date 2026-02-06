#include <stdio.h>

extern "C" int dnsmasq_rr_mx(void);

int main() {
    int mx = dnsmasq_rr_mx();
    printf("dnsmasq_rr_mx(): %d\n", mx);
    return 0;
}
