ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Autotools projects
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build and install libreadtags (the C library provided by universal-ctags)
WORKDIR /fuzz/src/libreadtags
RUN ./autogen.sh && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static && \
    make -j"$(nproc)" && \
    make install

# Ensure the install tree exists
RUN ls -R /fuzz/install
