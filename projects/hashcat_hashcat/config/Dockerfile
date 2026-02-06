ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build and install hashcat as a shared library and headers
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
# Build and install with SHARED=1 to produce libhashcat and install headers
RUN make -j"$(nproc)" SHARED=1 PREFIX=/fuzz/install && \
    make -j"$(nproc)" SHARED=1 PREFIX=/fuzz/install install && \
    bash -lc 'cd /fuzz/install/lib && if ls libhashcat.so.* 1>/dev/null 2>&1; then ln -sf $(ls -1 libhashcat.so.* | head -n1) libhashcat.so; fi'
