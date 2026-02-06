ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for nDPI
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext \
    flex bison \
    libpcap-dev libjson-c-dev libpcre2-dev libmaxminddb-dev libnuma-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig

WORKDIR /fuzz/src

# Generate configure script
RUN ./autogen.sh

# Configure for static library only and custom prefix
RUN ./configure \
      --prefix=/fuzz/install \
      --with-only-libndpi \
      --disable-shared \
      --enable-static

# Build and install
RUN make -j"$(nproc)" && make install
