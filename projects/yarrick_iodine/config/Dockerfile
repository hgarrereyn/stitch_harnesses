ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Build binaries and objects
RUN make -C /fuzz/src -j"$(nproc)" CC=${CC}
# Install binaries and docs
RUN make -C /fuzz/src -j"$(nproc)" CC=${CC} prefix=/fuzz/install install

# Create a static library from built objects and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/iodine \
 && ar rcs /fuzz/install/lib/libiodine.a /fuzz/src/src/*.o \
 && cp /fuzz/src/src/*.h /fuzz/install/include/iodine/
