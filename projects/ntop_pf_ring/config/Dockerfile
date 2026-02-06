ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    binutils \
    libnl-3-dev libnl-genl-3-dev \
    libpcap-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install PF_RING userland library
WORKDIR /fuzz/src/userland
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install && \
    make -C lib -j$(nproc) && \
    make -C lib install

# Ensure kernel header is available to consumers
RUN mkdir -p /fuzz/install/include/linux && \
    cp /fuzz/src/kernel/linux/pf_ring.h /fuzz/install/include/linux/
