ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config \
    python3-docutils python3-sphinx graphviz \
    libpcre2-dev libedit-dev libncursesw5-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install Varnish (libvarnishapi)
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install && \
    make -j$(nproc) && \
    make install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
