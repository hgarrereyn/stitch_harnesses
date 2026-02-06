ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for BlueZ library build
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libglib2.0-dev libdbus-1-dev \
    make gcc g++ \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Bootstrap autotools and configure with minimal components, install prefix /fuzz/install
RUN ./bootstrap && \
    ./configure \
      --prefix=/fuzz/install \
      --disable-systemd \
      --disable-tools \
      --disable-client \
      --disable-monitor \
      --disable-cups \
      --disable-udev \
      --disable-manpages \
      --disable-datafiles \
      --disable-obex \
      --disable-a2dp \
      --disable-avrcp \
      --disable-network \
      --disable-hid \
      --disable-hog \
      --disable-bap \
      --disable-bass \
      --disable-mcp \
      --disable-ccp \
      --disable-vcp \
      --disable-micp \
      --disable-csip \
      --disable-tmap \
      --disable-gmap \
      --disable-asha \
      --disable-hfp \
      --disable-midi \
      --disable-testing \
      --disable-experimental \
      --disable-deprecated \
      --enable-library \
    && \
    make -j"$(nproc)" && \
    make install

# Ensure library path exists for linking
RUN ls -l /fuzz/install/lib && ls -l /fuzz/install/include/bluetooth
