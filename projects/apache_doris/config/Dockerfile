ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies required to build and run a minimal Doris util hashing library (OpenSSL)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libssl-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from Apache Doris util/md5.cpp
# Source is already in /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Create install prefix
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/doris/util

# Build static library
WORKDIR /fuzz/src
RUN $CXX -O2 -fPIC -I/fuzz/src/be/src -c be/src/util/md5.cpp -o /tmp/md5.o \
    && ar rcs /fuzz/install/lib/libdorishash.a /tmp/md5.o \
    && rm -f /tmp/md5.o

# Install public headers
RUN cp be/src/util/md5.h /fuzz/install/include/doris/util/

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
