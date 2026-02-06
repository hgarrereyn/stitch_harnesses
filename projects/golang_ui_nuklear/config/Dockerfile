ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build a static library from the provided C sources and install headers
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Copy public headers
RUN cp /fuzz/src/nk/nuklear.h ${PREFIX}/include/ && \
    cp /fuzz/src/nk/nk.h ${PREFIX}/include/

# Build static library using required compilers
RUN set -eux; \
    gf_libafl_cc -I/fuzz/src/nk -c /fuzz/src/nk/nk.c -o /tmp/nk.o; \
    echo '#define NK_IMPLEMENTATION' > /tmp/nuklear_impl.c; \
    echo '#define NK_INCLUDE_FIXED_TYPES' >> /tmp/nuklear_impl.c; \
    echo '#define NK_INCLUDE_STANDARD_VARARGS' >> /tmp/nuklear_impl.c; \
    echo '#define NK_INCLUDE_STANDARD_IO' >> /tmp/nuklear_impl.c; \
    echo '#include "/fuzz/src/nk/nuklear.h"' >> /tmp/nuklear_impl.c; \
    gf_libafl_cc -I/fuzz/src/nk -c /tmp/nuklear_impl.c -o /tmp/nuklear_impl.o; \
    ar rcs ${PREFIX}/lib/libnuklear.a /tmp/nuklear_impl.o /tmp/nk.o; \
    rm -f /tmp/nuklear_impl.c /tmp/nuklear_impl.o /tmp/nk.o
