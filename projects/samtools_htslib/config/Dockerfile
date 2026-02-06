ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    zlib1g-dev libbz2-dev liblzma-dev \
    libcurl4-openssl-dev libdeflate-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build and install htslib
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN autoreconf -i
# Build static library if possible
RUN ./configure --prefix=/fuzz/install --disable-shared --enable-static \
    && make -j"$(nproc)" \
    && make install

