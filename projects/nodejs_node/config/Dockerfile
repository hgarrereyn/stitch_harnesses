ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    python3-distutils \
    pkg-config \
    g++ \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Prepare environment
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Configure and install headers only (faster, sufficient for building against API)
RUN ./configure --prefix=${PREFIX} && \
    python3 tools/install.py install --headers-only --prefix=${PREFIX}
