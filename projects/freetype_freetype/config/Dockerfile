ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build FreeType as a static library and install it to /fuzz/install
# We disable optional third-party dependencies to keep linking simple.
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config \
    ; \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build with CMake (out-of-source), static library only
RUN cmake -S . -B build \
      -G Ninja \
      -D CMAKE_BUILD_TYPE=Release \
      -D CMAKE_INSTALL_PREFIX=/fuzz/install \
      -D BUILD_SHARED_LIBS=OFF \
      -D FT_DISABLE_ZLIB=TRUE \
      -D FT_DISABLE_BZIP2=TRUE \
      -D FT_DISABLE_PNG=TRUE \
      -D FT_DISABLE_HARFBUZZ=TRUE \
      -D FT_DISABLE_BROTLI=TRUE \
    && cmake --build build -j$(nproc) \
    && cmake --build build --target install
