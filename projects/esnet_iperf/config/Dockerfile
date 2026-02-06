ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra build/runtime dependencies (minimal)
# We avoid optional OpenSSL/SCTP dev dependencies to keep the image small.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        pkg-config \
        file \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with the fuzzing compilers and install prefix. Build static library only.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --enable-static \
      --without-openssl \
    && make -j"$(nproc)" \
    && make install

