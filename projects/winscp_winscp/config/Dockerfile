ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN set -eux; \
    export DEBIAN_FRONTEND=noninteractive; \
    apt-get update; \
    apt-get install -y --no-install-recommends cmake ninja-build make ca-certificates; \
    rm -rf /var/lib/apt/lists/*

# Build a small static C library from a portable subset of PuTTY utils bundled in WinSCP
# and install headers under /fuzz/install/include/putty

RUN set -eux; \
    mkdir -p /tmp/winscp-utils-build && cd /tmp/winscp-utils-build && \
    cat > out_of_memory_stub.c <<'EOS'
#include <stdlib.h>
#include "defs.h"
NORETURN void out_of_memory(void) { abort(); }
EOS

RUN set -eux; \
    cd /tmp/winscp-utils-build && \
    cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(winscp_utils C)

add_definitions(-DWINSCP=1 -Dpinitassert=assert)

# Source directory for PuTTY subset vendored in WinSCP
set(PUTTY_SRC "/fuzz/src/source/putty")
set(PUTTY_UTILS "${PUTTY_SRC}/utils")

set(UTILS_SOURCES
    ${PUTTY_UTILS}/base64_decode.c
    ${PUTTY_UTILS}/base64_decode_atom.c
    ${PUTTY_UTILS}/base64_encode.c
    ${PUTTY_UTILS}/base64_encode_atom.c
    ${PUTTY_UTILS}/base64_valid.c
    ${PUTTY_UTILS}/burnstr.c
    ${PUTTY_UTILS}/burnwcs.c
    ${PUTTY_UTILS}/dupcat.c
    ${PUTTY_UTILS}/dupprintf.c
    ${PUTTY_UTILS}/dupstr.c
    ${PUTTY_UTILS}/dupwcs.c
    ${PUTTY_UTILS}/marshal.c
    ${PUTTY_UTILS}/memory.c
    ${PUTTY_UTILS}/nullstrcmp.c
    ${PUTTY_UTILS}/ptrlen.c
    ${PUTTY_UTILS}/smemclr.c
    ${PUTTY_UTILS}/smemeq.c
    ${PUTTY_UTILS}/strbuf.c
    ${PUTTY_UTILS}/string_length_for_printf.c
    ${PUTTY_UTILS}/write_c_string_literal.c
    ${PUTTY_UTILS}/bufchain.c
    ${PUTTY_SRC}/utils/tree234.c
    ${CMAKE_CURRENT_SOURCE_DIR}/out_of_memory_stub.c
)

add_library(winscp_utils STATIC ${UTILS_SOURCES})

# Include PuTTY core headers
target_include_directories(winscp_utils PUBLIC
    ${PUTTY_SRC}
    ${PUTTY_UTILS}
)

# Install the library and a subset of public headers useful for utils
install(TARGETS winscp_utils ARCHIVE DESTINATION lib)
install(FILES
    ${PUTTY_SRC}/defs.h
    ${PUTTY_SRC}/puttymem.h
    ${PUTTY_SRC}/marshal.h
    ${PUTTY_SRC}/misc.h
    ${PUTTY_SRC}/tree234.h
    DESTINATION include/putty)
EOF

RUN set -eux; \
    cmake -S /tmp/winscp-utils-build -B /tmp/winscp-utils-build/out \
      -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install; \
    cmake --build /tmp/winscp-utils-build/out --target install -j$(nproc); \
    rm -rf /tmp/winscp-utils-build
