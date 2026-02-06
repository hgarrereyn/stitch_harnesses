ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

# Build static library manually and install headers
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/miniaudio \
 && gf_libafl_cc -O2 -c miniaudio.c -o /fuzz/build/miniaudio.o \
 && ar rcs /fuzz/install/lib/libminiaudio.a /fuzz/build/miniaudio.o \
 && cp miniaudio.h /fuzz/install/include/miniaudio/
