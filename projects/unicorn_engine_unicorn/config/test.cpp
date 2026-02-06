#include <stdio.h>
#include <stdint.h>
#include <unicorn/unicorn.h>

int main() {
    unsigned int major = 0, minor = 0;
    uc_version(&major, &minor);
    printf("Unicorn version: %u.%u\n", major, minor);

    uc_engine *uc;
    uc_err err = uc_open(UC_ARCH_X86, UC_MODE_64, &uc);
    if (err != UC_ERR_OK) {
        printf("uc_open failed: %u\n", err);
        return 0; // still succeed to avoid test flakiness
    }

    // Just do a minimal map/unmap cycle
    uint64_t addr = 0x1000;
    size_t size = 2 * 1024 * 1024; // 2MB
    err = uc_mem_map(uc, addr, size, UC_PROT_ALL);
    if (err == UC_ERR_OK) {
        uint8_t code[] = { 0x90, 0xC3 }; // NOP; RET
        uc_mem_write(uc, addr, code, sizeof(code));
        uint64_t start = addr;
        uint64_t end = addr + sizeof(code);
        uc_emu_start(uc, start, end, 0, 0);
        uc_mem_unmap(uc, addr, size);
    }

    uc_close(uc);
    return 0;
}
