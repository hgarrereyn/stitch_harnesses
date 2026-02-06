ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    python3-setuptools \
    python3-tomli \
    meson \
    ninja-build \
    pkg-config \
    libglib2.0-dev \
 && rm -rf /var/lib/apt/lists/*

# Set compilers (clang-17 wrappers provided by the base image)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure a minimal build (no emulators/tools), custom prefix
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-system \
    --disable-user \
    --disable-tools \
    --disable-docs \
    --disable-guest-agent \
    --disable-werror

# Build just the utility library
RUN ninja -C build libqemuutil.a || (make -j$(nproc) && ninja -C build libqemuutil.a)

# Install headers and generated config headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp -r include/* /fuzz/install/include/ && \
    cp build/config-host.h /fuzz/install/include/ && \
    cp build/config-poison.h /fuzz/install/include/

# Repackage libqemuutil.a (thin) into a full archive for external linking
RUN set -eux; \
    tmpdir=$(mktemp -d); \
    cd "$tmpdir"; \
    ar t /fuzz/src/build/libqemuutil.a | while read -r f; do cp "$f" .; done; \
    ar rcs /fuzz/install/lib/libqemuutil.a *.o; \
    rm -rf "$tmpdir"
