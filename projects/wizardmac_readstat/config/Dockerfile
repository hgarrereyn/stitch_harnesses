ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    zlib1g-dev libcsv-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install ReadStat
WORKDIR /fuzz/src
RUN ./autogen.sh && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --enable-static --disable-shared && \
    make -j"$(nproc)" && \
    make install
