#include <stdio.h>
#include <string.h>
#include <libelf.h>
#include <gelf.h>

int main() {
    if (elf_version(EV_CURRENT) == EV_NONE) {
        printf("libelf version mismatch\\n");
        return 0;
    }
    const char data[] = { '\x7f','E','L','F', 2, 1, 1, 0 }; // minimal ELF ident
    Elf *e = elf_memory((char*)data, sizeof(data));
    if (!e) {
        printf("elf_memory failed as expected for tiny buffer: %s\\n", elf_errmsg(-1));
    } else {
        size_t n;
        if (elf_getphdrnum(e, &n) == 0) {
            printf("phnum=%zu\\n", n);
        }
        elf_end(e);
    }
    printf("libelf basic call OK\\n");
    return 0;
}
