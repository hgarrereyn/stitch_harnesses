ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    libtool \
    automake \
    autoconf \
    ca-certificates \
    file \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install ICU4C (static libs only)
WORKDIR /fuzz/src/icu4c/source
RUN ./configure \
    --disable-shared --enable-static \
    --prefix=/fuzz/install \
    --with-data-packaging=static \
    CC=${CC} CXX=${CXX} \
 && make -j"$(nproc)" \
 && make install

# Ensure library path exists
RUN ls -l /fuzz/install && ls -l /fuzz/install/lib && ls -l /fuzz/install/include/unicode || true
