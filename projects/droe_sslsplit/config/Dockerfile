ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN mkdir -p /fuzz/install/include /fuzz/install/lib /work

# Compile just the base64 module as a C library with the required compilers
RUN gf_libafl_cc -std=c99 -O2 -D_GNU_SOURCE -fPIC -I/fuzz/src -c /fuzz/src/base64.c -o /work/base64.o

# Create a static library
RUN ar rcs /fuzz/install/lib/libsslsplit.a /work/base64.o && ranlib /fuzz/install/lib/libsslsplit.a

# Install public headers needed by the library
RUN cp /fuzz/src/base64.h /fuzz/install/include/ && \
    cp /fuzz/src/attrib.h /fuzz/install/include/
