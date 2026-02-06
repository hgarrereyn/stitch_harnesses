ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    meson \
    ninja-build \
    libfuse3-dev \
    libglib2.0-dev \
    python3 \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install with Meson/Ninja
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
RUN meson setup build --prefix=/fuzz/install && \
    ninja -C build && \
    ninja -C build install

# Build and install a small static library exposing the cache API
# This allows linking a test/fuzz target against a stable API
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    sh -lc 'stitch_libafl_cc -DFUSE_USE_VERSION=31 -c cache.c -o /tmp/cache.o $(pkg-config --cflags fuse3 glib-2.0 gthread-2.0)' && \
    ar rcs /fuzz/install/lib/libsshfs_cache.a /tmp/cache.o && \
    install -m 0644 cache.h /fuzz/install/include/cache.h
