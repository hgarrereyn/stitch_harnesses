ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Configure, build static libs only, and install
RUN ./autogen.sh --prefix=${PREFIX} --disable-shared --enable-static --without-cython \
 && make -j"$(nproc)" \
 && make install \
 && ldconfig || true
