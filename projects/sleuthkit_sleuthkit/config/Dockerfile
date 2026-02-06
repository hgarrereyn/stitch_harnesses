ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libsqlite3-dev libssl-dev zlib1g-dev \
    perl \
    && rm -rf /var/lib/apt/lists/*

# Configure and build Sleuth Kit
WORKDIR /fuzz/src

# Generate configure script (when building from repo)
RUN ./bootstrap

# Configure with fuzzing compilers and install prefix; prefer static libs
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared --enable-static \
    --without-afflib --without-libaff4 --without-libewf --without-libqcow \
    --without-libvhdi --without-libvmdk --without-libvslvm --without-libbfio

# Build and install
RUN make -j"$(nproc)" && make install
