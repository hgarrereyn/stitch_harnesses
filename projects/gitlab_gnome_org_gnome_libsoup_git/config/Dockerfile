ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config python3 \
    libglib2.0-dev libnghttp2-dev libpsl-dev zlib1g-dev libsqlite3-dev libkrb5-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build with Meson (shared library to simplify linking)
RUN meson setup build \
    --prefix=/fuzz/install \
    -Ddefault_library=shared \
    -Dintrospection=disabled \
    -Dvapi=disabled \
    -Ddocs=disabled \
    -Dtests=false \
    -Dsysprof=disabled \
    -Dbrotli=disabled \
    -Dtls_check=false \
    && meson compile -C build -j$(nproc) \
    && meson install -C build
