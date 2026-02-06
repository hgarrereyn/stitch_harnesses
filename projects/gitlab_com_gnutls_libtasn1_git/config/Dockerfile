ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool make pkg-config bison help2man \
    ca-certificates git \
    && rm -rf /var/lib/apt/lists/*

# Build and install libtasn1 (static preferred)
WORKDIR /fuzz/src

# Generate configure script and build system files
RUN ./bootstrap

# Configure with fuzzing compilers and install prefix; prefer static lib and disable docs
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --disable-doc

# Build and install
RUN make -j"$(nproc)" && make install
