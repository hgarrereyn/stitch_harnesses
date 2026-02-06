ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    make bison flex ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install the library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Build static library with relaxed warnings and install to /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && make static=yes relaxed_build=on INSTALL=/fuzz/install \
 && make static=yes relaxed_build=on INSTALL=/fuzz/install install
