ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies for nginx (PCRE for rewrite, zlib for gzip)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libpcre3-dev zlib1g-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use fuzzing compilers
ENV CC=stitch_libafl_cc

# Configure, build, and install nginx to /fuzz/install
RUN ./auto/configure --prefix=/fuzz/install \
 && make -j"$(nproc)" \
 && make install

# Install a minimal header set to expose a tiny public interface for testing
RUN mkdir -p /fuzz/install/include \
 && cp src/core/nginx.h /fuzz/install/include/
