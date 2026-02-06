#include <cstdio>
#include <cstring>
#include <cstdlib>
extern "C" {
#include <protobuf-c/protobuf-c.h>
}

int main() {
    // Simple smoke test: create a buffer and append some bytes via the API
    unsigned char storage[16];
    ProtobufCBufferSimple simple = PROTOBUF_C_BUFFER_SIMPLE_INIT(storage);
    ProtobufCBuffer *buf = &simple.base;
    const unsigned char hello[] = { 'H','i','!' };
    protobuf_c_buffer_simple_append(buf, sizeof(hello), hello);

    // Confirm that it appended the expected number of bytes
    if (simple.len != sizeof(hello)) {
        return 1;
    }

    // Clean up
    PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&simple);

    // Another trivial API use: check a NULL message is invalid
    if (protobuf_c_message_check(NULL)) {
        return 1;
    }

    std::puts("protobuf-c smoke test OK");
    return 0;
}
