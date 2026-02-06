#include <stdio.h>
#include <inttypes.h>
#include <capstone/capstone.h>

int main() {
    csh handle;
    cs_insn *insn;
    size_t count;

    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
        printf("cs_open failed\n");
        return 1;
    }

    // Enable detail for operands
    cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

    // Bytes: push rbp; mov rax, [rip + 0x13b8]
    uint8_t code[] = {0x55, 0x48, 0x8b, 0x05, 0xb8, 0x13, 0x00, 0x00};

    count = cs_disasm(handle, code, sizeof(code), 0x1000, 0, &insn);
    if (count == 0) {
        printf("Disassembly failed\n");
        cs_close(&handle);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("0x%" PRIx64 ": \t%s\t\t%s\n", insn[i].address, insn[i].mnemonic, insn[i].op_str);
    }

    cs_free(insn, count);
    cs_close(&handle);
    return 0;
}
