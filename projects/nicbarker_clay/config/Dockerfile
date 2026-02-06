ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install tools to build a tiny static library from the single-header project
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

# Build a static library from clay.h and install headers and library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build

# Create a tiny C translation unit that implements clay
RUN printf "#define CLAY_IMPLEMENTATION\n#include \"/fuzz/src/clay.h\"\n" > /tmp/build/clay_lib.c

# Compile and archive into a static library
RUN stitch_libafl_cc -O2 -fPIC -I/fuzz/src -c /tmp/build/clay_lib.c -o /tmp/build/clay_lib.o && \
    ar rcs /fuzz/install/lib/libclay.a /tmp/build/clay_lib.o

# Install the original header
RUN cp /fuzz/src/clay.h /fuzz/install/include/

# Install a C++17 compatibility wrapper header that relaxes the language check
RUN printf '#ifndef CLAY_COMPAT_H\n#define CLAY_COMPAT_H\n// Force the C99 path in clay.h so it can be included from C++17\n#ifndef __STDC__\n#define __STDC__ 1\n#endif\n#ifndef __STDC_VERSION__\n#define __STDC_VERSION__ 199901L\n#endif\n#include "clay.h"\n#endif // CLAY_COMPAT_H\n' > /fuzz/install/include/clay_compat.h
