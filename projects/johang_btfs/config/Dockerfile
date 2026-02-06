ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake pkg-config \
    libfuse3-dev libtorrent-rasterbar-dev libcurl4-openssl-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install
WORKDIR /fuzz/src
RUN autoreconf -i
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install
RUN make -j"$(nproc)" && make install

# Ensure headers are available for consumers
RUN mkdir -p /fuzz/install/include && \
    cp -a src/btfs.h src/btfsstat.h /fuzz/install/include/ || true
