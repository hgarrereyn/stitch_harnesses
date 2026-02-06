ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates git make autoconf automake libtool pkg-config python3 gperf \
    libcap-dev libseccomp-dev libyajl-dev libsystemd-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Fetch submodules (libocispec)
RUN git submodule update --init --recursive

# Configure, build and install (static library by default via LT_INIT(disable-shared))
RUN ./autogen.sh \
 && ./configure --prefix=${PREFIX} \
 && make -j"$(nproc)" \
 && make install
