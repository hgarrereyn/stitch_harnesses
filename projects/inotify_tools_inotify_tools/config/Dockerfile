ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate build system and configure
RUN autoreconf -fi
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static

# Build and install
RUN make -j"$(nproc)" && make install
