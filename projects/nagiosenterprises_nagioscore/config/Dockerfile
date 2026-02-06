ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build Nagios libnagios and install development headers
ENV DEBIAN_FRONTEND=noninteractive

# Install minimal dependencies (make is preinstalled in base image)
RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install \
 && make -j"$(nproc)" -C lib \
 && make -j"$(nproc)" install-devel

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
