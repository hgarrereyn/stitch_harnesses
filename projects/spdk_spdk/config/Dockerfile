ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies to run configure and generate headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN ./configure \
      --prefix=/fuzz/install \
      --disable-tests \
      --disable-unit-tests \
      --disable-examples \
      --disable-apps \
      --without-shared \
      --without-rdma \
      --without-fc \
      --without-rbd \
      --without-daos \
      --without-virtio \
      --without-vhost \
      --without-vfio-user \
      --without-fio \
      --without-dpdk-compressdev \
      --without-ocf \
      --without-ublk \
      --without-fsdev \
      --without-iscsi-initiator \
      --without-usdt \
      --without-uring \
      --without-avahi \
      --without-golang \
      --without-nvme-cuse

# Generate only headers (config.h and version.h)
RUN make -j"$(nproc)" include/spdk/config.h include/spdk/version.h build_dir

# Manually install headers into /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp -r include/spdk /fuzz/install/include/
