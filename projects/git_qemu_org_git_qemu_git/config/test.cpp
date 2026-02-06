extern "C" {
#include <qemu/osdep.h>
#include <qemu/uuid.h>
}
#include <stdio.h>

int main() {
    QemuUUID u1, u2;
    qemu_uuid_generate(&u1);
    qemu_uuid_generate(&u2);

    char s1[UUID_STR_LEN];
    char s2[UUID_STR_LEN];
    qemu_uuid_unparse(&u1, s1);
    qemu_uuid_unparse(&u2, s2);

    printf("uuid1=%s\n", s1);
    printf("uuid2=%s\n", s2);
    printf("equal=%d null1=%d null2=%d\n", qemu_uuid_is_equal(&u1, &u2), qemu_uuid_is_null(&u1), qemu_uuid_is_null(&u2));

    // parse and hash
    QemuUUID p;
    if (qemu_uuid_parse(s1, &p) == 0) {
        printf("hash=%u\n", (unsigned)qemu_uuid_hash(&p));
    }

    return 0;
}
