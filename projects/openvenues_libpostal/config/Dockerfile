ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script
RUN ./bootstrap.sh

# Configure for static build, set compilers, install prefix, and disable data download to keep image small
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure \
      --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --disable-data-download

# Build and install
RUN make -j"$(nproc)" && make install
