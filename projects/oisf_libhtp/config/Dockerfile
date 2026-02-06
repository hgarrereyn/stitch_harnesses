ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate autotools, configure with fuzzing compilers, build static if possible, install
RUN chmod +x autogen.sh && \
    ./autogen.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install --enable-static --disable-shared && \
    make -j"$(nproc)" && \
    make install
