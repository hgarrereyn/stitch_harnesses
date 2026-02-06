ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: meson (via pip), nasm for x86 asm, and pkg-config
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 python3-pip python3-setuptools python3-wheel \
    nasm pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir meson

# Build and install dav1d statically with meson/ninja
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig

WORKDIR /fuzz/src
RUN meson setup build \
      --default-library=static \
      --prefix=/fuzz/install \
      --libdir=lib \
      --buildtype=release \
    && ninja -C build \
    && meson install -C build
