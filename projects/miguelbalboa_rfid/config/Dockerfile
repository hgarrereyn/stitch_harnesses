ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN mkdir -p /tmp/shims ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib

# Create minimal Arduino shim
RUN /bin/sh -lc 'printf "%s\n" \
"#ifndef ARDUINO_SHIM_H" \
"#define ARDUINO_SHIM_H" \
"#include <stdint.h>" \
"#include <stdlib.h>" \
"#include <string.h>" \
"#include <chrono>" \
"#include <thread>" \
"typedef uint8_t byte;" \
"struct __FlashStringHelper {};" \
"#ifndef HIGH" \
"#define HIGH 0x1" \
"#endif" \
"#ifndef LOW" \
"#define LOW  0x0" \
"#endif" \
"#ifndef INPUT" \
"#define INPUT 0x0" \
"#endif" \
"#ifndef OUTPUT" \
"#define OUTPUT 0x1" \
"#endif" \
"#ifndef MSBFIRST" \
"#define MSBFIRST 1" \
"#endif" \
"#ifndef SPI_MODE0" \
"#define SPI_MODE0 0" \
"#endif" \
"#ifndef SS" \
"#define SS 10" \
"#endif" \
"#ifndef F" \
"#define F(x) ((const __FlashStringHelper*)(x))" \
"#endif" \
"#ifndef PROGMEM" \
"#define PROGMEM" \
"#endif" \
"#ifndef pgm_read_byte" \
"#define pgm_read_byte(addr) (*(const unsigned char*)(addr))" \
"#endif" \
"#ifndef HEX" \
"#define HEX 16" \
"#endif" \
"#ifndef DEC" \
"#define DEC 10" \
"#endif" \
"class SerialShim {" \
"public:" \
"    void begin(unsigned long) {}" \
"    void println() {}" \
"    void println(const __FlashStringHelper*) {}" \
"    template<typename T> void println(const T&) {}" \
"    template<typename T> void println(const T&, int) {}" \
"    void print(const __FlashStringHelper*) {}" \
"    template<typename T> void print(const T&) {}" \
"    template<typename T> void print(const T&, int) {}" \
"};" \
"static SerialShim Serial;" \
"static inline void pinMode(uint8_t, uint8_t) {}" \
"static inline void digitalWrite(uint8_t, uint8_t) {}" \
"static inline int digitalRead(uint8_t) { return LOW; }" \
"static inline void yield() {}" \
"static inline unsigned long millis() { using namespace std::chrono; static const auto start = steady_clock::now(); return (unsigned long)duration_cast<milliseconds>(steady_clock::now()-start).count(); }" \
"static inline void delay(unsigned long ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }" \
"static inline void delayMicroseconds(unsigned int us) { std::this_thread::sleep_for(std::chrono::microseconds(us)); }" \
"#endif // ARDUINO_SHIM_H" \
> /tmp/shims/Arduino.h'

# Create minimal SPI shim
RUN /bin/sh -lc 'printf "%s\n" \
"#ifndef SPI_SHIM_H" \
"#define SPI_SHIM_H" \
"#include <stdint.h>" \
"#include \"Arduino.h\"" \
"class SPISettings {" \
"public:" \
"    SPISettings(uint32_t, uint8_t, uint8_t) {}" \
"};" \
"class SPIClass {" \
"public:" \
"    void begin() {}" \
"    void beginTransaction(const SPISettings&) {}" \
"    void endTransaction() {}" \
"    uint8_t transfer(uint8_t) { return 0; }" \
"};" \
"static SPIClass SPI;" \
"#endif // SPI_SHIM_H" \
> /tmp/shims/SPI.h'

# Build static library from sources
WORKDIR /fuzz/src
RUN $CXX -I/tmp/shims -I/fuzz/src/src -fPIC -c src/MFRC522.cpp -o /tmp/MFRC522.o
RUN $CXX -I/tmp/shims -I/fuzz/src/src -fPIC -c src/MFRC522Extended.cpp -o /tmp/MFRC522Extended.o
RUN ar rcs /tmp/libmfrc522.a /tmp/MFRC522.o /tmp/MFRC522Extended.o && cp /tmp/libmfrc522.a ${INSTALL_PREFIX}/lib/

# Install headers (including shims)
RUN cp -t ${INSTALL_PREFIX}/include \
    /fuzz/src/src/MFRC522.h \
    /fuzz/src/src/MFRC522Extended.h \
    /fuzz/src/src/deprecated.h \
    /fuzz/src/src/require_cpp11.h \
    /tmp/shims/Arduino.h \
    /tmp/shims/SPI.h
