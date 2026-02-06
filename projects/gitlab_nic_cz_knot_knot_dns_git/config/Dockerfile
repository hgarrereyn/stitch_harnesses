ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make \
    libgnutls28-dev liblmdb-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Configure, build, and install only the libraries (static) into /fuzz/install
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN autoreconf -if
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-daemon \
    --disable-utilities \
    --disable-documentation \
    --disable-modules \
    --disable-shared \
    --enable-static \
    --disable-redis \
    --disable-quic \
    --disable-xdp \
    --disable-dnstap
RUN make -j"$(nproc)" && make install
