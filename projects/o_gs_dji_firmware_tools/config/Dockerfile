ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    make ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install a tiny static C++ shim library that exposes a minimal API
# so the fuzzer can link against something when the upstream project has only Python/Lua tools.
ENV INSTALL_PREFIX=/fuzz/install
RUN mkdir -p /tmp/shim && \
    printf '%s\n' \
'#include <string>' \
'namespace djitools {' \
'const char* version() {' \
'    return "o_gs_dji_firmware_tools shim 1.0";' \
'}' \
'int simple_checksum(const unsigned char* data, int len) {' \
'    unsigned int sum = 0;' \
'    for (int i = 0; i < len; ++i) sum += data[i];' \
'    return (int)(sum & 0xFFFF);' \
'}' \
'} // namespace djitools' \
> /tmp/shim/djitools.cpp && \
    printf '%s\n' \
'#pragma once' \
'#include <cstddef>' \
'namespace djitools {' \
'// Returns a static version string for the shim.' \
'const char* version();' \
'// Returns a 16-bit additive checksum of the given buffer.' \
'int simple_checksum(const unsigned char* data, int len);' \
'} // namespace djitools' \
> /tmp/shim/djitools.h && \
    stitch_libafl_cxx -O2 -fPIC -c /tmp/shim/djitools.cpp -o /tmp/shim/djitools.o && \
    ar rcs /tmp/shim/libdjifwtools.a /tmp/shim/djitools.o && \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include && \
    cp /tmp/shim/libdjifwtools.a ${INSTALL_PREFIX}/lib/ && \
    cp /tmp/shim/djitools.h ${INSTALL_PREFIX}/include/

# Keep source available (not building Python tools here, only providing headers/libs for fuzzing harness)
WORKDIR /fuzz/src
