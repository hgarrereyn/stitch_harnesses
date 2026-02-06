ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (for ar) if not present
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Prepare install dirs
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib

# Install public header
RUN cp /fuzz/src/nuklear.h /fuzz/install/include/

# Build a static library from the single-header implementation
RUN set -eux; \
    printf '%s\n' \
      '#define NK_IMPLEMENTATION' \
      '#define NK_INCLUDE_DEFAULT_ALLOCATOR' \
      '#define NK_INCLUDE_STANDARD_IO' \
      '#define NK_INCLUDE_STANDARD_VARARGS' \
      '#define NK_INCLUDE_STANDARD_STRING' \
      '#define NK_INCLUDE_FIXED_TYPES' \
      '#define NK_INCLUDE_STANDARD_BOOL' \
      '#include "nuklear.h"' \
      > /fuzz/build/nuklear_impl.c \
 && stitch_libafl_cc -O2 -fPIC -I/fuzz/src -c /fuzz/build/nuklear_impl.c -o /fuzz/build/nuklear_impl.o \
 && ar rcs /fuzz/install/lib/libnuklear.a /fuzz/build/nuklear_impl.o \
 && ranlib /fuzz/install/lib/libnuklear.a
