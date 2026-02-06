#include <stdio.h>
#include <stdint.h>
#include <wson.h>

int main() {
    // Create a buffer and serialize a small map: {"a": 1, "b": true}
    wson_buffer* buf = wson_buffer_new();
    wson_push_type_map(buf, 2);               // two entries
    wson_push_property(buf, "a", 1);
    wson_push_type_int(buf, 1);
    wson_push_property(buf, "b", 1);
    wson_push_type_boolean(buf, 1);

    // Read back
    wson_buffer* rd = wson_buffer_from(buf->data, buf->length);
    int8_t type = wson_next_type(rd);
    if (type != WSON_MAP_TYPE) {
        printf("Unexpected type: %d\n", (int)type);
        return 1;
    }
    uint32_t sz = wson_next_uint(rd);
    printf("map size=%u\n", sz);

    // Clean up
    wson_buffer_free(buf);
    // rd references the same underlying memory; do not free rd->data
    free(rd);
    return 0;
}
