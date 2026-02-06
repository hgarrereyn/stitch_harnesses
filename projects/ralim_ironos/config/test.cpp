#include <cstdio>
#include <cstring>
#include <vector>
extern "C" {
#include <brieflz.h>
}

int main() {
    const char* msg = "IronOS BriefLZ test data: 1234567890abcdefghijklmnopqrstuvwxyz";
    size_t src_size = strlen(msg);

    size_t max_comp = blz_max_packed_size(src_size);
    size_t work_sz = blz_workmem_size(src_size);

    std::vector<unsigned char> work(work_sz);
    std::vector<unsigned char> comp(max_comp);
    std::vector<unsigned char> decomp(src_size);

    unsigned long comp_size = blz_pack(msg, comp.data(), (unsigned long)src_size, work.data());
    if (comp_size == 0 || comp_size > comp.size()) {
        printf("Compression failed\n");
        return 1;
    }

    unsigned long dec_size = blz_depack(comp.data(), decomp.data(), (unsigned long)src_size);
    if (dec_size != src_size) {
        printf("Decompression size mismatch: %lu vs %zu\n", dec_size, src_size);
        return 1;
    }

    if (memcmp(msg, decomp.data(), src_size) != 0) {
        printf("Data mismatch\n");
        return 1;
    }

    printf("OK: comp=%lu, src=%zu\n", comp_size, src_size);
    return 0;
}
