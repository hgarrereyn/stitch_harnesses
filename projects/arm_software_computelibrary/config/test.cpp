#include <cstdio>
#include "arm_compute/AclVersion.h"

int main() {
    const AclVersion* v = AclVersionInfo();
    if (!v) {
        printf("No version info\n");
        return 1;
    }
    printf("ACL version: %d.%d.%d - %s\n", v->major, v->minor, v->patch, v->build_info ? v->build_info : "(null)");
    return 0;
}
