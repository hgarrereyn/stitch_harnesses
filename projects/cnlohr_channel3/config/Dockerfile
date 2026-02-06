ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV AR=ar
ENV RANLIB=ranlib

# Generate tables using the provided generators
WORKDIR /fuzz/src/tablemaker
RUN make

# Create fake headers to satisfy minimal dependencies for table headers
RUN mkdir -p /fuzz/build/fake_include && \
    printf "#ifndef C_TYPES_H\n#define C_TYPES_H\n#include <stdint.h>\n#include <stddef.h>\n#define ICACHE_FLASH_ATTR\ntypedef uint8_t u8_t;\ntypedef uint16_t u16_t;\ntypedef uint32_t u32_t;\n#endif\n" > /fuzz/build/fake_include/c_types.h && \
    printf "#ifndef ESP82XXUTIL_H\n#define ESP82XXUTIL_H\n/* Stub for host build */\n#endif\n" > /fuzz/build/fake_include/esp82xxutil.h

# Build a minimal static library exposing the generated tables
WORKDIR /fuzz/build
RUN ${CC} -O2 -I/fuzz/build/fake_include -I/fuzz/src/tablemaker -c /fuzz/src/tablemaker/broadcast_tables.c -o broadcast_tables.o && \
    ${CC} -O2 -I/fuzz/build/fake_include -I/fuzz/src/tablemaker -c /fuzz/src/tablemaker/CbTable.c -o CbTable.o && \
    ${AR} rcs libchannel3.a broadcast_tables.o CbTable.o

# Install headers and library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/tablemaker/broadcast_tables.h /fuzz/install/include/ && \
    cp /fuzz/src/tablemaker/CbTable.h /fuzz/install/include/ && \
    cp /fuzz/build/fake_include/c_types.h /fuzz/install/include/ && \
    cp /fuzz/build/fake_include/esp82xxutil.h /fuzz/install/include/ && \
    cp /fuzz/build/libchannel3.a /fuzz/install/lib/
