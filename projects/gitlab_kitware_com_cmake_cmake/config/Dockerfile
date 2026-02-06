ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build CMake using its bootstrap script to avoid needing a pre-existing CMake
# Ensure required basic build tools are present
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build using the fuzzing compiler wrappers
WORKDIR /fuzz/src
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./bootstrap --prefix=/fuzz/install

RUN make -j"$(nproc)"
RUN make install

# Extract the core static library and a small header we will use as a public API
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/cmake \
 && cp ./Source/libCMakeLib.a /fuzz/install/lib/ \
 && cp ./Source/cmVersion.h /fuzz/install/include/cmake/
