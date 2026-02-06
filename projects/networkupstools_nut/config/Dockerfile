ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    autoconf automake libtool pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install
WORKDIR /fuzz/src

# Generate configure script
RUN ./autogen.sh

# Configure with fuzzing compilers and minimal features; install headers for public API
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure \
      --prefix=/fuzz/install \
      --enable-static --disable-shared \
      --with-all=no \
      --with-dev=yes \
      --without-ssl \
      --without-doc --without-docs || { cat config.log || true; exit 1; }

# Build and install
RUN make -j"$(nproc)" && make install
