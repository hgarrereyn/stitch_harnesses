ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    perl \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with clang wrappers and install prefix
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure PostgreSQL; disable optional features to keep build small
RUN ./configure --prefix=/fuzz/install \
    --without-readline \
    --without-zlib \
    --disable-nls || { cat config.log || true; exit 1; }

# Build and install only headers and libpq (client library)
RUN make -j"$(nproc)" -C src/include install && \
    make -j"$(nproc)" -C src/interfaces/libpq install
