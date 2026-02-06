ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install libnestegg statically
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN autoreconf --install --force
RUN ./configure --prefix=/fuzz/install --disable-shared --enable-static
RUN make -j"$(nproc)" && make install
