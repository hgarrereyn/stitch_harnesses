ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext \
    libev-dev libpcre2-dev libudns-dev \
    make gcc g++ \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script
RUN ./autogen.sh

# Configure with fuzzing compilers and install prefix
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --enable-dns --prefix=/fuzz/install

# Build and install the project
RUN make -j$(nproc) && make install

# Create a minimal static library exposing useful APIs for testing/linking
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/sniproxy \
    && ar rcs /fuzz/install/lib/libsniproxy.a src/logger.o \
    && cp -a src/logger.h /fuzz/install/include/sniproxy/
