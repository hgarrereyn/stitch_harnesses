#include <cstdio>
#include <cstdint>
#include <cpuinfo.h>

int main() {
    if (!cpuinfo_initialize()) {
        std::printf("cpuinfo_initialize() failed or unsupported.\n");
        return 0;
    }

    const struct cpuinfo_processor* proc0 = cpuinfo_get_processor(0);
    const struct cpuinfo_package* pkg0 = cpuinfo_get_package(0);
    if (proc0 && proc0->core && pkg0) {
        std::printf("Package: %s\n", pkg0->name ? pkg0->name : "unknown");
        std::printf("Core uarch id: %u\n", (unsigned)proc0->core->uarch);
        if (proc0->cache.l1d) {
            std::printf("L1d size: %u\n", (unsigned)proc0->cache.l1d->size);
        }
    } else {
        std::printf("cpuinfo data not available.\n");
    }

#if CPUINFO_ARCH_X86 || CPUINFO_ARCH_X86_64
    std::printf("AVX support: %s\n", cpuinfo_has_x86_avx() ? "yes" : "no");
#elif CPUINFO_ARCH_ARM || CPUINFO_ARCH_ARM64
    std::printf("NEON support: %s\n", cpuinfo_has_arm_neon() ? "yes" : "no");
#elif CPUINFO_ARCH_RISCV || CPUINFO_ARCH_RISCV64
    std::printf("RVV support: %s\n", cpuinfo_has_riscv_v() ? "yes" : "no");
#else
    std::printf("Unknown arch.\n");
#endif

    return 0;
}
