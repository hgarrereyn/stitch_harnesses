ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies to compile libpcap (static)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    make \
    gcc \
    flex \
    bison \
    pkg-config \
    ca-certificates \
    file \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/libpcap
# Configure, build, and install static libpcap into /fuzz/install using the required compiler
RUN CC=gf_libafl_cc ./configure \
      --disable-protochain \
      --disable-rdma \
      --disable-shared \
      --disable-usb \
      --disable-netmap \
      --disable-bluetooth \
      --disable-dbus \
      --without-libnl \
      --without-dpdk \
      --prefix=/fuzz/install && \
    make -j$(nproc) && \
    make install
