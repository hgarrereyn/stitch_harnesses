ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build prerequisites
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    bison \
    flex \
    perl \
    pkg-config \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure for a minimal client-only static build and install to /fuzz/install
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --without-readline \
      --without-zlib \
      --without-openssl

# Build and install just libpq and headers to keep image size and build time down
RUN make -C src/include -j"$(nproc)" all \
 && make -C src/interfaces/libpq -j"$(nproc)" \
 && make -C src/interfaces/libpq install \
 && make -C src/common install \
 && make -C src/port install \
 && make -C src/include install
