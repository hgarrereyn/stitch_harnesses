ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build and install Kore
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
RUN make PREFIX=/fuzz/install && make install PREFIX=/fuzz/install
