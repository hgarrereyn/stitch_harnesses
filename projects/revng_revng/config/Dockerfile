ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Install headers into /fuzz/install to provide the public API for building tests
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/include/* /fuzz/install/include/
