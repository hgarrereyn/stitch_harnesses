ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: meson + ninja + pkg-config
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      meson ninja-build pkg-config python3 ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build and install pistache statically with Meson
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN meson setup build \
      --buildtype=release \
      --prefix=/fuzz/install \
      --libdir=/fuzz/install/lib \
      -Ddefault_library=static \
      -DPISTACHE_INSTALL=true \
      -DPISTACHE_BUILD_TESTS=false \
      -DPISTACHE_BUILD_EXAMPLES=false \
      -DPISTACHE_BUILD_DOCS=false \
      -DPISTACHE_USE_SSL=false \
      -DPISTACHE_USE_RAPIDJSON=false \
      -DPISTACHE_USE_CONTENT_ENCODING_BROTLI=false \
      -DPISTACHE_USE_CONTENT_ENCODING_DEFLATE=false \
      -DPISTACHE_USE_CONTENT_ENCODING_ZSTD=false && \
    meson compile -C build && \
    meson install -C build
