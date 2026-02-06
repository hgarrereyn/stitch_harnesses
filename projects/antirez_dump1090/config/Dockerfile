ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static library from the project's anet.* (network helpers)
# We avoid librtlsdr dependency by not building the dump1090 binary.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build static libanet.a and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include
WORKDIR /fuzz/src
RUN $CC -O2 -g -Wall -W -fPIC -c anet.c -o anet.o \
    && ar rcs libanet.a anet.o \
    && ranlib libanet.a \
    && cp libanet.a /fuzz/install/lib/ \
    && cp anet.h /fuzz/install/include/

