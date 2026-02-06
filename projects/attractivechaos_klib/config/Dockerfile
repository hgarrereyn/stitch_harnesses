ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for optional components (zlib, curl) and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    zlib1g-dev \
    libcurl4-openssl-dev \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

# Build a static library from selected C sources and install headers
RUN set -eux; \
    mkdir -p /fuzz/build "$PREFIX"/lib "$PREFIX"/include; \
    cd /fuzz/build; \
    for c in /fuzz/src/*.c; do \
      [ -f "$c" ] || continue; \
      base=$(basename "$c"); \
      case "$base" in \
        kurl.c|kopen.c) echo "Skipping $base"; continue ;; \
      esac; \
      $CC -O2 -fPIC -I/fuzz/src -c "$c" -o "${base%.c}.o"; \
    done; \
    ar rcs libklib.a *.o; \
    cp libklib.a "$PREFIX"/lib/; \
    cp /fuzz/src/*.h "$PREFIX"/include/; \
    mkdir -p "$PREFIX"/include/cpp; \
    if [ -d /fuzz/src/cpp ]; then cp -r /fuzz/src/cpp/*.hpp "$PREFIX"/include/cpp/; fi
