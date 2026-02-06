ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and Ghostscript development headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libgs-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Bootstrap autotools and configure with fuzzing compilers
RUN autoreconf -fi \
 && CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static \
 && make -j"$(nproc)" \
 && make install
