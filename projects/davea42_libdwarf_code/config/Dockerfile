ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (meson + pkg-config). Ninja is preinstalled in base image.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config python3 && \
    rm -rf /var/lib/apt/lists/*

# Configure, build, and install libdwarf statically with decompression disabled (no zlib/zstd deps)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build in /fuzz/build and install to /fuzz/install
RUN meson setup /fuzz/build /fuzz/src \
    --prefix=/fuzz/install \
    --libdir=lib \
    --buildtype=release \
    --default-library static \
    -Ddecompression=false \
    -Dwerror=false && \
    ninja -C /fuzz/build && \
    ninja -C /fuzz/build install
