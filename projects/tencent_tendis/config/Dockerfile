ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal setup: install headers only for building external programs
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/src/tendisplus/include/*.h /fuzz/install/include/ || true

# Provide lib and bin dirs for consistency
RUN mkdir -p /fuzz/install/lib /fuzz/install/bin

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
