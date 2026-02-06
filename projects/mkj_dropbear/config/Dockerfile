ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies (zlib optional, but harmless)
RUN apt-get update && apt-get install -y --no-install-recommends \
    zlib1g-dev \
  && rm -rf /var/lib/apt/lists/*

# Build and install Dropbear
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Configure: disable PAM and zlib to keep dependencies minimal, install to /fuzz/install
RUN ./configure --prefix=/fuzz/install --disable-pam --disable-zlib

# Build selected programs (no need for strip here)
RUN make -j"$(nproc)" PROGRAMS="dropbear dbclient dropbearkey dropbearconvert scp"

# Install binaries
RUN make install

# Install public API headers for plugins
RUN mkdir -p /fuzz/install/include/dropbear \
 && cp -v src/pubkeyapi.h /fuzz/install/include/dropbear/
