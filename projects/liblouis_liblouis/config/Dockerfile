ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script and build static library only
RUN ./autogen.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --disable-shared --enable-static --without-yaml --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install
