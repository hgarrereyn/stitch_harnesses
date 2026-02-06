#include <cstdio>
#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>

int main() {
    // Just create a TCP context and exercise a few non-I/O APIs
    modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
    if (!ctx) {
        std::printf("Failed to create modbus context\n");
        return 1;
    }

    modbus_set_debug(ctx, 0);
    modbus_set_slave(ctx, 1);

    // Create and free a mapping structure
    modbus_mapping_t *mapping = modbus_mapping_new(10, 10, 10, 10);
    if (mapping) {
        // Exercise a couple of helpers on a bit array (each entry is one bit)
        uint8_t bits[16] = {0};
        modbus_set_bits_from_byte(bits, 0, 0xA5);
        (void)modbus_get_byte_from_bits(bits, 0, 8);
        modbus_mapping_free(mapping);
    }

    int header_len = modbus_get_header_length(ctx);
    std::printf("Header length: %d\n", header_len);

    modbus_free(ctx);
    return 0;
}
