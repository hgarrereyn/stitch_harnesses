ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        meson python3 pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set compilers to fuzzer wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure, build, and install libpsl statically using Meson
WORKDIR /fuzz/src
RUN meson setup builddir \
        -Ddefault_library=static \
        -Dprefix=/fuzz/install \
        -Dlibdir=lib \
        -Dtests=false \
        -Druntime=no \
    && meson compile -C builddir \
    && meson install -C builddir
