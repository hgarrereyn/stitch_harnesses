#include <cstdio>
#include <soem/soem.h>

int main() {
    const char* s1 = ec_sdoerror2string(0x00000000u);
    const char* s2 = ec_ALstatuscode2string(0u);
    const char* s3 = ec_soeerror2string(0u);
    const char* s4 = ec_mbxerror2string(0u);
    std::printf("SDO: %s\nAL: %s\nSoE: %s\nMBX: %s\n", s1 ? s1 : "(null)", s2 ? s2 : "(null)", s3 ? s3 : "(null)", s4 ? s4 : "(null)");
    return 0;
}
