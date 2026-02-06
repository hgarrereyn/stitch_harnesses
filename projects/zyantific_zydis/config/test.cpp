#include <Zydis/Zydis.h>
#include <stdio.h>

int main() {
    ZydisDecoder decoder;
    if (ZYAN_FAILED(ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64))) {
        printf("Decoder init failed\n");
        return 1;
    }

    ZydisFormatter formatter;
    if (ZYAN_FAILED(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) {
        printf("Formatter init failed\n");
        return 1;
    }

    const uint8_t data[] = { 0x51, 0xC3 }; // push rcx; ret
    ZyanUSize offset = 0;
    ZyanUSize length = sizeof(data);

    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

    while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, data + offset, length - offset, &instruction, operands))) {
        char buffer[128];
        if (ZYAN_SUCCESS(ZydisFormatterFormatInstruction(&formatter, &instruction, operands, instruction.operand_count_visible, buffer, sizeof(buffer), 0 /*runtime_address*/, NULL /*user_data*/))) {
            printf("%s\n", buffer);
        }
        offset += instruction.length;
        if (offset >= length) break;
    }

    return 0;
}
