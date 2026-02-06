ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for libusb (autotools, pkg-config, libudev)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      autoconf automake libtool pkg-config libudev-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure scripts
RUN ./autogen.sh

# Configure for static library build and install prefix
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --disable-shared --enable-static --prefix=/fuzz/install

# Build and install
RUN make -j"$(nproc)" && make install
