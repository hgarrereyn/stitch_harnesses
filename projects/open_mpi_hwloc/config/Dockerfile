ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools build from git
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Generate configure script and build static-only library with minimal optional deps
RUN ./autogen.sh && \
    ./configure \
      --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --disable-libxml2 \
      --without-cuda --without-cudart --without-opencl --without-gl --without-levelzero --without-nvml --without-rsmi \
      && \
    make -j"$(nproc)" && \
    make install
