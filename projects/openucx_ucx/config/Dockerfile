ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autoconf/automake project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make gcc g++ \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Generate configure scripts if needed and build
RUN ./autogen.sh && \
    ./contrib/configure-release --prefix=${PREFIX} \
      --enable-devel-headers=no --enable-examples=no --enable-test-apps=no \
      --enable-debug-data=no && \
    make -j"$(nproc)" && \
    make install
