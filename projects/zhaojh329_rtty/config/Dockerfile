ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from available sources (utils.c) and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cd /fuzz/src/src && \
    gf_libafl_cc -O2 -fPIC -c utils.c -o /tmp/utils.o && \
    ar rcs /fuzz/install/lib/librtty.a /tmp/utils.o && \
    cp utils.h /fuzz/install/include/

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:/usr/lib/pkgconfig:/usr/lib/x86_64-linux-gnu/pkgconfig
