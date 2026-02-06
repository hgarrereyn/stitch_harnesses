ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

# Build only the static library and install headers
RUN make -j$(nproc) CC=stitch_libafl_cc CXX=stitch_libafl_cxx AR=ar liblzma.a && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp liblzma.a /fuzz/install/lib/ && \
    cp sdk/C/*.h /fuzz/install/include/
