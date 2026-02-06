ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install libunwind statically using the provided clang wrappers
WORKDIR /fuzz/src

# Generate configure script (building from git)
RUN autoreconf -i

# Configure: static only; disable optional libs to keep dependencies minimal
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared --enable-static \
    --disable-coredump --disable-ptrace --disable-setjmp --disable-tests --disable-documentation

# Build and install
RUN make -j"$(nproc)" && make install
