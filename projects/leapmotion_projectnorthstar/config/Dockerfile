ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any build dependencies (none required beyond base tools)
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Prepare install dirs
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/include/arduino /fuzz/install/lib

# Create stub Arduino headers to satisfy includes when building for Linux
RUN printf "#pragma once\n#include <stdint.h>\n#include <stdlib.h>\n#include <stdio.h>\n#include <stdarg.h>\n\n#define INPUT_PULLUP 0x2\n#define INPUT 0x0\n#define OUTPUT 0x1\n#define LOW 0\n#define HIGH 1\n#define RISING 1\n#define CHANGE 2\n#define A0 14\n#define A1 15\n#define A2 16\n\nstatic inline void pinMode(uint32_t, uint32_t) {}\nstatic inline void digitalWrite(uint32_t, uint32_t) {}\nstatic inline void analogWrite(uint32_t, uint32_t) {}\nstatic inline void attachInterrupt(uint32_t, void (*)(void), uint32_t) {}\nstatic inline void detachInterrupt(uint32_t) {}\nstatic inline int digitalRead(uint32_t){ return 1; }\nstatic inline uint32_t digitalPinToInterrupt(uint32_t p){ return p; }\nstatic inline void delay(unsigned long) {}\n\nstruct SerialClass {\n  void begin(unsigned long, int=0) {}\n  void print(const char*) {}\n  void printf(const char*, ...) {}\n};\nstatic SerialClass Serial;\n\nstruct TwoWire { void begin(){} };\nstatic TwoWire Wire;\n\ntemplate<typename T> static inline T constrain(T x, T a, T b){ return x<a?a:(x>b?b:x); }\n" > /fuzz/build/Arduino.h && \
    printf "#pragma once\n" > /fuzz/build/wiring_private.h && \
    printf "#pragma once\n" > /fuzz/build/Wire.h && \
    printf "#pragma once\n" > /fuzz/build/debug.h

# Create a minimal stub implementation of the TPS61194_ class to avoid MCU-specific code
RUN printf "#include <stdint.h>\n#include \"tps61194.h\"\nvoid VSYNC_IRQ(void) {}\nuint32_t g_TPS_pinId_pwmPin = 0;\nTPS61194_::TPS61194_(uint32_t,uint32_t,uint32_t){}\nTPS61194_::~TPS61194_(void){}\nvoid TPS61194_::setup(TPS61194_::TPS_config_vsyncType_t, uint8_t, uint16_t, uint16_t){}\nvoid TPS61194_::brightness(uint16_t){}\nvoid TPS61194_::powerOn(void){}\nvoid TPS61194_::powerOff(void){}\nvoid TPS61194_::lightOn(void){}\nvoid TPS61194_::lightOff(void){}\n" > /fuzz/build/tps61194_stub.cpp

# Build the static library from the stub implementation
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ${CXX} -std=c++17 -I/fuzz/build -I/fuzz/src/Electronics/Firmware/src/Program/Lib_TPS61194 -c tps61194_stub.cpp -o tps61194_stub.o && \
    ar rcs libnorthstar.a tps61194_stub.o && \
    cp libnorthstar.a /fuzz/install/lib/

# Install public headers and stub includes
RUN cp /fuzz/src/Electronics/Firmware/src/Program/Lib_TPS61194/tps61194.h /fuzz/install/include/ && \
    cp /fuzz/build/Arduino.h /fuzz/install/include/arduino/ && \
    cp /fuzz/build/wiring_private.h /fuzz/install/include/arduino/ && \
    cp /fuzz/build/Wire.h /fuzz/install/include/arduino/
