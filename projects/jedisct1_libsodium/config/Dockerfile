ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build and install libsodium statically
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./autogen.sh -s && \
    ./configure --disable-shared --enable-static --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install
