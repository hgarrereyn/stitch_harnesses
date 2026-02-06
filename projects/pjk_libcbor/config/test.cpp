#include <cbor.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    // Build a small CBOR map and serialize it
    cbor_item_t* root = cbor_new_definite_map(1);
    if (!root) return 1;

    struct cbor_pair pair;
    pair.key = cbor_move(cbor_build_string("hello"));
    pair.value = cbor_move(cbor_build_uint8(123));
    if (!cbor_map_add(root, pair)) {
        cbor_decref(&root);
        return 1;
    }

    unsigned char* buffer = nullptr;
    size_t buffer_size = 0;
    cbor_serialize_alloc(root, &buffer, &buffer_size);

    // Print size to ensure something happened
    std::printf("CBOR size: %zu\n", buffer_size);

    free(buffer);
    cbor_decref(&root);
    return 0;
}
