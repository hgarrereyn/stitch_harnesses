ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal, host-buildable subset: libb64 (Base64 encoder/decoder)
# from cores/esp8266/libb64, providing a tiny pgmspace.h compatibility shim.

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build/compat; \
    printf "#ifndef PGM_COMPAT\n#define PGM_COMPAT\n#define PROGMEM\nstatic inline unsigned char pgm_read_byte(const void* p){return *(const unsigned char*)p;}\n#endif\n" > /tmp/build/compat/pgmspace.h; \
    cd /tmp/build; \
    gf_libafl_cxx -c -O2 -fPIC -I/fuzz/src/cores/esp8266/libb64 -I/tmp/build/compat /fuzz/src/cores/esp8266/libb64/cencode.cpp -o cencode.o; \
    gf_libafl_cxx -c -O2 -fPIC -I/fuzz/src/cores/esp8266/libb64 -I/tmp/build/compat /fuzz/src/cores/esp8266/libb64/cdecode.cpp -o cdecode.o; \
    ar rcs /fuzz/install/lib/libesp8266_libb64.a cencode.o cdecode.o; \
    cp /fuzz/src/cores/esp8266/libb64/cencode.h /fuzz/install/include/; \
    cp /fuzz/src/cores/esp8266/libb64/cdecode.h /fuzz/install/include/; \
    rm -rf /tmp/build
