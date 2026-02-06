ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libpng-dev zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install jbig2dec as a static library
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static && \
    make -j$(nproc) && \
    make install

# Ensure libraries are discoverable
ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:$PKG_CONFIG_PATH
ENV LD_LIBRARY_PATH=/fuzz/install/lib:$LD_LIBRARY_PATH
