ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: yasm for x86 asm, and minimal runtime deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    yasm \
 && rm -rf /var/lib/apt/lists/*

# Build and install static libvpx
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p build && cd build \
 && ../configure \
      --prefix=/fuzz/install \
      --disable-examples \
      --disable-tools \
      --disable-docs \
      --enable-static \
      --disable-shared \
      --enable-vp8 \
      --enable-vp9 \
      --target=x86_64-linux-gcc \
 && make -j"$(nproc)" \
 && make install
