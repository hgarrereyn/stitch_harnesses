ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build and install libsass statically
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install
RUN make -j"$(nproc)" static && \
    make install-headers PREFIX=/fuzz/install && \
    make install-static PREFIX=/fuzz/install

# Done. The library and headers are now in /fuzz/install
