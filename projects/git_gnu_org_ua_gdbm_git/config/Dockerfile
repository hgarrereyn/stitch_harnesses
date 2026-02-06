ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool gettext autopoint pkg-config make gcc g++ rsync texinfo \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Generate build system (from git) and configure static build
RUN ./bootstrap && \
    ./configure --prefix=${PREFIX} --disable-shared --enable-static \
                --without-readline --enable-libgdbm-compat --disable-nls && \
    make -j$(nproc) && \
    make install
