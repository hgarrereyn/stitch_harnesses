ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates build-essential && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from portable Marlin sources
WORKDIR /fuzz/src

# Create install dirs
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Build crc16 as a static library using the required compilers
RUN stitch_libafl_cc -c -O2 -IMarlin/src/libs -o /tmp/crc16.o Marlin/src/libs/crc16.cpp \
 && ar rcs /fuzz/install/lib/libmarlinutils.a /tmp/crc16.o \
 && cp Marlin/src/libs/crc16.h /fuzz/install/include/

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
