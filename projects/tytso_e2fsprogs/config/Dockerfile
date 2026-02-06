ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install only static libraries
WORKDIR /fuzz/src
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --disable-shared --enable-static --disable-nls --prefix=/fuzz/install
RUN make -j"$(nproc)" && make install
