ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from Kodi sources: xbmc/utils/Base64
# Install headers and library to /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

# Build and install static lib
RUN mkdir -p /fuzz/install/include/xbmc/utils /fuzz/install/lib /tmp/build \
 && ${CXX} -c -O2 -fPIC -I/fuzz/src/xbmc/utils -o /tmp/build/Base64.o /fuzz/src/xbmc/utils/Base64.cpp \
 && ar rcs /fuzz/install/lib/libkodi_base64.a /tmp/build/Base64.o \
 && cp /fuzz/src/xbmc/utils/Base64.h /fuzz/install/include/xbmc/utils/
