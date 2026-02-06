ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build libexif statically and install to /fuzz/install
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use autopoint to provide gettext infrastructure, then autoreconf, then build/install
RUN autopoint -f && autoreconf -fi && \
    mkdir -p build && cd build && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ../configure \
      --prefix=/fuzz/install \
      --disable-shared --enable-static \
      --disable-docs \
      --disable-nls && \
    make -j"$(nproc)" && \
    make install
