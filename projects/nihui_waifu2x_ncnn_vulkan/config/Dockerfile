ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra deps needed for header-only usage

# Install headers into /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/src/filesystem_utils.h /fuzz/install/include/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
ENV CFLAGS="" CXXFLAGS="" LDFLAGS=""
ENV PREFIX=/fuzz/install
