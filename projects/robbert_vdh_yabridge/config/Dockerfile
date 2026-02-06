ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix and copy public headers from mounted source tree
RUN mkdir -p /fuzz/install/include/vestige \
 && cp /fuzz/src/src/include/vestige/aeffectx.h /fuzz/install/include/vestige/aeffectx.h

# Environment variables for compilers (not used here since we don't build the project)
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install
