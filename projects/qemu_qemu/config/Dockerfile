ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps for QEMU's configure/meson flow
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson ninja-build pkg-config python3 python3-setuptools python3-venv python3-tomli libglib2.0-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure a minimal build that does not build any emulators/tools, to still generate build system
WORKDIR /fuzz/src
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-werror \
      --disable-system \
      --disable-user \
      --disable-tools \
      --disable-docs \
      --disable-guest-agent

# Build and install (installs minimal runtime tree; we will also install specific headers we use)
RUN ninja -C build -j"$(nproc)" && ninja -C build install

# Install only the public headers we intend to use
RUN mkdir -p /fuzz/install/include/qemu \
    && cp include/qemu/compiler.h /fuzz/install/include/qemu/ \
    && cp include/qemu/typedefs.h /fuzz/install/include/qemu/ \
    && cp include/qemu/target-info.h /fuzz/install/include/qemu/ \
    && cp include/qemu/bswap.h /fuzz/install/include/qemu/
