ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint \
    build-essential \
    libssl-dev libdevmapper-dev libpopt-dev uuid-dev libjson-c-dev libblkid-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure environment to use the provided clang wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Generate configure script and build just the library, statically
RUN ./autogen.sh && \
    ./configure \
      --prefix=/fuzz/install \
      --disable-asciidoc \
      --disable-nls \
      --disable-external-tokens \
      --disable-ssh-token \
      --disable-keyring \
      --disable-kernel_crypto \
      --disable-cryptsetup \
      --disable-veritysetup \
      --disable-integritysetup \
      --enable-static \
      --disable-shared \
    && make -j"$(nproc)" \
    && make install
