ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools-based project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Generate configure script, configure and build static library, then install
RUN ./autogen.sh \
 && ./configure --prefix=${PREFIX} --disable-shared --with-embedded-libevent \
      --without-snmp --without-readline \
 && make -j"$(nproc)" \
 && make install
