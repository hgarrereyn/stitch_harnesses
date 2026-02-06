ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies for autotools/libtool projects
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libtool \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install rtpproxy as a static library with the public header
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install --enable-librtpproxy=yes
RUN make -j"$(nproc)" && make install

