ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Generate configure script and build static lib only
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static && \
    make -j"$(nproc)" && \
    make install
