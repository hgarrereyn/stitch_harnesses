#include <brunsli/encode.h>
#include <vector>
#include <cstddef>
#include <cstdio>

static size_t Sink(void* out_data, const unsigned char* buf, size_t size) {
    std::vector<unsigned char>* v = reinterpret_cast<std::vector<unsigned char>*>(out_data);
    v->insert(v->end(), buf, buf + size);
    return size; // consume all
}

int main() {
    const unsigned char* input = nullptr;
    size_t input_size = 0;
    std::vector<unsigned char> enc;

    int enc_ok = EncodeBrunsli(input_size, input, &enc, Sink);
    std::printf("EncodeBrunsli returned %d, out size: %zu\n", enc_ok, enc.size());

    return 0;
}
