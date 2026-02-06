ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make git \
    bison flex \
    libxml2-dev libreadline-dev libselinux1-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install Augeas from source at /fuzz/src
WORKDIR /fuzz/src

# Configure with fuzzing compilers and install prefix; build static libs only
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./autogen.sh --disable-shared --enable-static --prefix=/fuzz/install
RUN make -j$(nproc) && make install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:${PKG_CONFIG_PATH}
