ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    make ca-certificates git \
    libusb-1.0-0-dev \
    binutils && \
    rm -rf /var/lib/apt/lists/*

# Build newer libplist (required by libimobiledevice-glue >= 2.3.0)
RUN git clone --depth 1 https://github.com/libimobiledevice/libplist.git /tmp/libplist && \
    cd /tmp/libplist && \
    ./autogen.sh --prefix=/usr && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /tmp/libplist

# Build dependency: libimobiledevice-glue (required by usbmuxd)
RUN git clone --depth 1 https://github.com/libimobiledevice/libimobiledevice-glue.git /tmp/glue && \
    cd /tmp/glue && \
    ./autogen.sh --prefix=/usr && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /tmp/glue

# Build and install usbmuxd
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN ./autogen.sh --prefix=/fuzz/install --without-preflight --without-systemd && \
    make -j"$(nproc)" && \
    make install

# Provide headers and a static archive for linking against internals
RUN set -e; \
    mkdir -p /fuzz/install/include/usbmuxd /fuzz/install/lib; \
    cp -a src/*.h /fuzz/install/include/usbmuxd/; \
    objs=$(find src -maxdepth 2 -type f -name '*.o' || true); \
    if [ -n "$objs" ]; then ar rcs /fuzz/install/lib/libusbmuxd-internal.a $objs; else echo 'No objects found'; fi
