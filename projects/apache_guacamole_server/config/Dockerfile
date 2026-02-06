ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and required libraries
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libcairo2-dev libpng-dev libjpeg-turbo8-dev uuid-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Bootstrap autotools, configure with fuzzing compilers, build static, and install
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN autoreconf -fi \
 && ./configure --prefix=/fuzz/install --disable-shared --enable-static \
 && make -j"$(nproc)" \
 && make install
