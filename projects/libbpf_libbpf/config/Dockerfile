ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for libbpf
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    pkg-config \
    libelf-dev \
    zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install static libbpf
WORKDIR /fuzz/src/src
ENV CC=stitch_libafl_cc
ENV PKG_CONFIG=pkg-config
# Install to /fuzz/install; build only static lib into OBJDIR=build
RUN make -j"$(nproc)" BUILD_STATIC_ONLY=y OBJDIR=build PREFIX=/fuzz/install && \
    make -j"$(nproc)" BUILD_STATIC_ONLY=y OBJDIR=build PREFIX=/fuzz/install install

# The library and headers are now in /fuzz/install
