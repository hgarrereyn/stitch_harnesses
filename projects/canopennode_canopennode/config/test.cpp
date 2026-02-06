#include <cstdio>
#include <cstdint>

// Use the FIFO utility from CANopenNode
#include "301/CO_fifo.h"

int main() {
    // Configure a small FIFO buffer
    uint8_t buffer[16];

    // Initialize FIFO
    CO_fifo_t fifo; // requires CO_CONFIG_FIFO to enable declarations
    CO_fifo_init(&fifo, buffer, sizeof(buffer));

    // Write a message
    const char* msg = "hello";
    size_t written = CO_fifo_write(&fifo, reinterpret_cast<const uint8_t*>(msg), 5, nullptr);

    // Read it back
    uint8_t out[16];
    bool_t eof = false;
    size_t read = CO_fifo_read(&fifo, out, sizeof(out), &eof);

    // Null-terminate and print
    out[read] = '\0';
    std::printf("written=%zu read=%zu eof=%d msg=%s\n", written, read, (int)eof, out);
    return 0;
}
