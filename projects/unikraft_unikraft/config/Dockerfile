ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build and install headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

# Install headers and create a tiny, empty static library for linking
RUN set -eux; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib ${PREFIX}/include/uk/print ${PREFIX}/include/uk/bits; \
    # Create minimal generated config forcing use of system libc for snprintf
    printf "#pragma once\n/* Minimal generated config for fuzz build */\n#define CONFIG_LIBNOLIBC 1\n\n" > ${PREFIX}/include/uk/bits/config.h; \
    # Install core headers
    cp -r ${SRC}/include/uk ${PREFIX}/include/; \
    # Expose snprintf API header in a stable include path
    cp ${SRC}/lib/ukprint/snprintf.h ${PREFIX}/include/uk/print/snprintf.h; \
    # Create a dummy static library to satisfy linker
    printf "void __unikraft_dummy(void){}" > /tmp/dummy.c; \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs ${PREFIX}/lib/libunikraft.a /tmp/dummy.o
