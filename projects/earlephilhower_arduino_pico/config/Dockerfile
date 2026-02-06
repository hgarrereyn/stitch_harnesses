ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a tiny, host-buildable subset of the project (libb64)
# into /fuzz/install as a static library
RUN set -eux; \
    install -d /fuzz/install/include/libb64 /fuzz/install/lib /tmp/buildlib; \
    printf "#pragma once\n#include <stdint.h>\n#define PROGMEM\nstatic inline uint8_t pgm_read_byte(const void* p){ return *(const uint8_t*)p; }\n" > /tmp/buildlib/pgmspace.h; \
    cd /tmp/buildlib; \
    gf_libafl_cxx -I/tmp/buildlib -I/fuzz/src/cores/rp2040/libb64 -c /fuzz/src/cores/rp2040/libb64/cencode.cpp -o cencode.o; \
    gf_libafl_cxx -I/tmp/buildlib -I/fuzz/src/cores/rp2040/libb64 -c /fuzz/src/cores/rp2040/libb64/cdecode.cpp -o cdecode.o; \
    ar rcs /fuzz/install/lib/libarduino_pico_b64.a cencode.o cdecode.o; \
    cp /fuzz/src/cores/rp2040/libb64/cencode.h /fuzz/install/include/libb64/; \
    cp /fuzz/src/cores/rp2040/libb64/cdecode.h /fuzz/install/include/libb64/; \
    rm -rf /tmp/buildlib
