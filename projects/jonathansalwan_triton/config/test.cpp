#include <triton/context.hpp>
#include <triton/archEnums.hpp>
#include <cstdint>
#include <iostream>

int main() {
    triton::Context ctx(triton::arch::ARCH_X86_64);

    auto &rax = ctx.getRegister("rax");
    ctx.setConcreteRegisterValue(rax, 0x12345678);
    auto val = ctx.getConcreteRegisterValue(rax);

    triton::arch::Instruction inst;
    const uint8_t code[] = {0x48, 0x31, 0xC0}; // xor rax, rax
    inst.setOpcode(code, sizeof(code));
    ctx.processing(inst);

    auto newVal = ctx.getConcreteRegisterValue(rax);

    std::cout << "Initial RAX: " << std::hex << (uint64_t)val << " New RAX: " << (uint64_t)newVal << std::endl;
    return 0;
}
