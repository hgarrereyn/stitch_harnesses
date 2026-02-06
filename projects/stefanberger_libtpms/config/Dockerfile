ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    autoconf automake libtool pkg-config \
    libssl-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install libtpms
WORKDIR /fuzz/src
RUN ./autogen.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install --libdir=/fuzz/install/lib \
                --disable-shared --enable-static \
                --with-openssl --with-tpm2 \
    && make -j"$(nproc)" \
    && make install
