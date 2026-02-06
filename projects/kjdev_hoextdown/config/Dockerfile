ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        gperf \
    && rm -rf /var/lib/apt/lists/*

# Build and install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN make -j"$(nproc)" && make PREFIX=/fuzz/install install
