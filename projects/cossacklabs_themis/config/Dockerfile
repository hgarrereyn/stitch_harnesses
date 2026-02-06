ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (OpenSSL headers/libs)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        libssl-dev pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build and install Themis with fuzzing compilers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Build and install (prefer OpenSSL engine)
RUN make -j"$(nproc)" ENGINE=openssl PREFIX=/fuzz/install && \
    make install ENGINE=openssl PREFIX=/fuzz/install
