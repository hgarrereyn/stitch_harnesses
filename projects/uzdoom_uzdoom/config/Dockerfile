ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    build-essential \
    pkg-config \
    libglib2.0-dev \
    python3 \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Use fuzzing compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure and build ZMusic standalone as a static library
RUN cmake -S /fuzz/src/libraries/ZMusic -B /fuzz/build/zmusic -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF

RUN cmake --build /fuzz/build/zmusic --target zmusic -j

# Install headers (if provided) and ensure the static library is copied
RUN cmake --install /fuzz/build/zmusic --component devel || true && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    ZMUSIC_LIB=$(find /fuzz/build/zmusic -name 'libzmusic.a' -type f | head -n1) && \
    cp "$ZMUSIC_LIB" /fuzz/install/lib/ && \
    test -f /fuzz/install/include/zmusic.h || cp /fuzz/src/libraries/ZMusic/include/zmusic.h /fuzz/install/include/
