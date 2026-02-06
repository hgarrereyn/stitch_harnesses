ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gperf perl python3 \
    && rm -rf /var/lib/apt/lists/*

# Use fuzzer compiler wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Generate configure script (but do not run configure yet)
RUN NOCONFIGURE=1 ./autogen.sh

# Configure: install to /fuzz/install and disable optional components to keep it small
RUN ./configure --prefix=/fuzz/install \
    --disable-contrib \
    --disable-fontconfig \
    --disable-dbus \
    --disable-gtk \
    --without-x \
    --without-ijs \
    --with-local-zlib \
    --with-local-brotli \
    --without-libidn \
    --without-libpaper \
    --without-pdftoraster \
    --with-pic

# Build and install core, install public headers, and ensure libgs is available
RUN make -j"$(nproc)" && make install && \
    mkdir -p /fuzz/install/include/ghostscript && \
    cp psi/iapi.h psi/ierrors.h base/gserrors.h /fuzz/install/include/ghostscript/ && \
    make -j"$(nproc)" bin/gs.a || true && \
    if [ -f bin/gs.a ]; then \
        mkdir -p /fuzz/install/lib && cp bin/gs.a /fuzz/install/lib/libgs.a; \
    else \
        make -j"$(nproc)" so && mkdir -p /fuzz/install/lib && cp sobin/libgs.so* /fuzz/install/lib/; \
    fi
