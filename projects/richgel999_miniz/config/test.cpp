#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// Use installed header path style
#include <miniz/miniz.h>

int main() {
    const std::string msg = std::string("Hello, miniz! ") + std::string(100, '*');
    const std::vector<unsigned char> input(msg.begin(), msg.end());

    uLong src_len = (uLong)input.size();
    uLong bound = compressBound(src_len);
    std::vector<unsigned char> compressed(bound);

    uLongf comp_len = bound;
    int cr = compress(compressed.data(), &comp_len, input.data(), src_len);
    if (cr != Z_OK) {
        std::printf("compress failed: %d\n", cr);
        return 1;
    }
    compressed.resize(comp_len);

    std::vector<unsigned char> output(src_len);
    uLongf out_len = src_len;
    int ur = uncompress(output.data(), &out_len, compressed.data(), comp_len);
    if (ur != Z_OK || out_len != src_len) {
        std::printf("uncompress failed: %d len %lu/%lu\n", ur, (unsigned long)out_len, (unsigned long)src_len);
        return 1;
    }

    bool same = std::memcmp(output.data(), input.data(), src_len) == 0;
    std::printf("comp %lu -> %lu, roundtrip ok: %s\n",
                (unsigned long)src_len, (unsigned long)comp_len, same ? "yes" : "no");
    return same ? 0 : 1;
}
