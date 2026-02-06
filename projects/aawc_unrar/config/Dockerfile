ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build static libunrar and install into /fuzz/install
WORKDIR /fuzz/src

# Build the library using provided makefile with required compilers
RUN make clean || true \
 && make -j"$(nproc)" lib CXX=stitch_libafl_cxx \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -a libunrar.a /fuzz/install/lib/ \
 && cp -a dll.hpp /fuzz/install/include/
