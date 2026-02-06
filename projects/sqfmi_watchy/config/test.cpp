#include <cstdio>
#include <cstdint>
#include <bma4_defs.h>
#include <bma4.h>
#include <bma423.h>

static uint16_t dummy_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    (void)dev_addr; (void)reg_addr; (void)data; (void)len;
    return 1; // non-zero indicates failure
}

static uint16_t dummy_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    (void)dev_addr; (void)reg_addr; (void)data; (void)len;
    return 1; // non-zero indicates failure
}

static void dummy_delay(uint32_t ms) { (void)ms; }

int main() {
    bma4_dev dev{};
    dev.dev_addr = BMA4_I2C_ADDR_PRIMARY;
    dev.interface = BMA4_I2C_INTERFACE;
    dev.bus_read = dummy_read;
    dev.bus_write = dummy_write;
    dev.delay = dummy_delay;
    dev.read_write_len = 8;
    dev.resolution = 12;
    dev.feature_len = BMA423_FEATURE_SIZE;

    // Try a few API calls; expect failures without hardware
    uint8_t status = 0;
    uint16_t rc1 = bma4_get_status(&status, &dev);

    uint16_t int_status = 0;
    uint16_t rc2 = bma4_read_int_status(&int_status, &dev);

    std::printf("bma4_get_status rc=%u, status=%u\n", (unsigned)rc1, (unsigned)status);
    std::printf("bma4_read_int_status rc=%u, istat=%u\n", (unsigned)rc2, (unsigned)int_status);
    return 0;
}
