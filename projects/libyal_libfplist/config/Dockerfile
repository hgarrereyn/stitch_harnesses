ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    gettext autopoint \
    make ninja-build \
    flex bison \
    git \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install libfplist and its vendored deps
WORKDIR /fuzz/src

# Sync vendored dependencies
RUN ./synclibs.sh

# Generate build system
RUN ./autogen.sh

# Configure with fuzzing compilers and static libs only
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --disable-shared --enable-static --prefix=/fuzz/install

# Build and install
RUN make -j"$(nproc)" && make install
