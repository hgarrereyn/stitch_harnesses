ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a static lib for Adafruit GFX with minimal Arduino stubs
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV SRC=/fuzz/src \
    PREFIX=/fuzz/install \
    BUILD=/fuzz/build \
    STUBS=/fuzz/stubs

RUN mkdir -p ${BUILD} ${PREFIX}/include ${PREFIX}/lib ${STUBS}

# Provide minimal Arduino environment stubs required to compile headers
RUN bash -lc 'printf %b "#ifndef ARDUINO_STUB_ARDUINO_H\n#define ARDUINO_STUB_ARDUINO_H\n#include <stdint.h>\n#include <stddef.h>\n#include <stdbool.h>\n#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n#ifndef PROGMEM\n#define PROGMEM\n#endif\n#ifndef F\n#define F(x) (x)\n#endif\n// Basic Arduino-like constants and stubs\n#ifndef HIGH\n#define HIGH 0x1\n#endif\n#ifndef LOW\n#define LOW  0x0\n#endif\n#ifndef INPUT\n#define INPUT 0x0\n#endif\n#ifndef OUTPUT\n#define OUTPUT 0x1\n#endif\n#ifndef SPI_MODE0\n#define SPI_MODE0 0x00\n#endif\nstatic inline void pinMode(int, int) {}\nstatic inline void digitalWrite(int, int) {}\nstatic inline void delay(unsigned long) {}\nstatic inline unsigned long millis(void) { return 0; }\n\ntypedef bool boolean;\ntypedef uint8_t byte;\nclass __FlashStringHelper;\nclass String {\npublic:\n  String() {}\n  String(const char*) {}\n  const char* c_str() const { return \"\"; }\n  size_t length() const { return 0; }\n};\n#endif\n" > ${STUBS}/Arduino.h'

RUN bash -lc 'printf %b "#ifndef ARDUINO_STUB_PRINT_H\n#define ARDUINO_STUB_PRINT_H\n#include <stddef.h>\n#include <stdint.h>\nclass Print {\npublic:\n  virtual ~Print() {}\n  virtual size_t write(uint8_t) = 0;\n  size_t write(const char* s) {\n    size_t n = 0;\n    if (s) { while (*s) { write((uint8_t)*s++); ++n; } }\n    return n;\n  }\n  size_t print(const char* s) { return write(s); }\n};\n#endif\n" > ${STUBS}/Print.h'

RUN bash -lc 'printf %b "#ifndef ARDUINO_STUB_SPI_H\n#define ARDUINO_STUB_SPI_H\n#include <stdint.h>\nclass SPISettings { public: SPISettings(uint32_t, uint8_t, uint8_t) {} };\nclass SPIClass { public: void begin() {} void endTransaction() {} void beginTransaction(const SPISettings&) {} uint8_t transfer(uint8_t v){return v;} };\nstatic SPIClass SPI;\n#endif\n" > ${STUBS}/SPI.h'

RUN bash -lc 'printf %b "#ifndef ARDUINO_STUB_WIRE_H\n#define ARDUINO_STUB_WIRE_H\n#include <stdint.h>\nclass TwoWire { public: void begin() {} };\nstatic TwoWire Wire;\n#endif\n" > ${STUBS}/Wire.h'

RUN bash -lc 'printf %b "#ifndef ADAFRUIT_STUB_I2CDEVICE_H\n#define ADAFRUIT_STUB_I2CDEVICE_H\n#include <stdint.h>\nclass Adafruit_I2CDevice { public: Adafruit_I2CDevice(uint8_t addr, void* theWire=nullptr) {} bool begin() { return true; } };\n#endif\n" > ${STUBS}/Adafruit_I2CDevice.h'

RUN bash -lc 'printf %b "#ifndef ADAFRUIT_STUB_SPIDEVICE_H\n#define ADAFRUIT_STUB_SPIDEVICE_H\n#include \"SPI.h\"\nclass Adafruit_SPIDevice { public: Adafruit_SPIDevice(int8_t cs, uint32_t freq=1000000, uint8_t bitOrder=0, uint8_t dataMode=0, void* spi=&SPI) {} bool begin() { return true; } };\n#endif\n" > ${STUBS}/Adafruit_SPIDevice.h'

# Build only the core GFX sources into a static library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN bash -lc "${CXX} -I${STUBS} -I${SRC} -DARDUINO=100 -fPIC -c ${SRC}/Adafruit_GFX.cpp -o ${BUILD}/Adafruit_GFX.o"
RUN bash -lc "${CC}  -I${STUBS} -I${SRC} -DARDUINO=100 -fPIC -c ${SRC}/glcdfont.c     -o ${BUILD}/glcdfont.o"
RUN bash -lc "ar rcs ${PREFIX}/lib/libadafruit_gfx.a ${BUILD}/Adafruit_GFX.o ${BUILD}/glcdfont.o"

# Install headers (originals) and stubs for downstream users
RUN cp -v ${SRC}/Adafruit_GFX.h ${SRC}/gfxfont.h ${SRC}/Adafruit_SPITFT.h ${SRC}/Adafruit_GrayOLED.h ${SRC}/Adafruit_SPITFT_Macros.h ${PREFIX}/include/ && \
    cp -v ${STUBS}/* ${PREFIX}/include/
