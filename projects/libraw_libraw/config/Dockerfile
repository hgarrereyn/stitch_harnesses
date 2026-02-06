ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    zlib1g-dev libjpeg-dev liblcms2-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Generate configure script
RUN autoreconf -fi

# Configure: static only, install prefix
RUN ./configure --disable-shared --enable-static \
    --disable-examples \
    --prefix=/fuzz/install

# Build and install
RUN make -j"$(nproc)" && make install
