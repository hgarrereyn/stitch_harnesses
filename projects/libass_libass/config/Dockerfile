ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libfreetype6-dev libfribidi-dev libharfbuzz-dev libfontconfig1-dev \
    nasm \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install libass (static)
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./autogen.sh && \
    ./configure \
      --prefix=/fuzz/install \
      --enable-static --disable-shared \
    && make -j"$(nproc)" \
    && make install
