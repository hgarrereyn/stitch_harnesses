ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools project
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf automake libtool autopoint gettext pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script
RUN autoreconf -vfi

# Configure with fuzzing compilers and static library only
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --without-ui \
    --without-readline

# Build and install
RUN make -j"$(nproc)" && make install
