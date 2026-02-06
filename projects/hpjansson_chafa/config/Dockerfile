ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libglib2.0-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install chafa (library only, static preferred)
WORKDIR /fuzz/src

# Generate build system and configure
RUN NOCONFIGURE=1 ./autogen.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure \
      --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --without-tools

# Build and install
RUN make -j"$(nproc)" && make install
