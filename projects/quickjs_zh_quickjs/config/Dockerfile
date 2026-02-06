ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools needed by Makefile (binutils for ar)
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Build and install QuickJS to /fuzz/install using fuzzing compilers
WORKDIR /fuzz/src

# Avoid strip requirement during install, set install prefix
# Use libAFL compilers as required
RUN make -j"$(nproc)" CC=stitch_libafl_cc STRIP=true PREFIX=/fuzz/install && \
    make -j"$(nproc)" CC=stitch_libafl_cc STRIP=true PREFIX=/fuzz/install install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
