ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: install the public header into /fuzz/install
# Set compilers as required (used if any build occurs)
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Create install prefix and copy header
RUN mkdir -p /fuzz/install/include \
 && cp /fuzz/src/testlib.h /fuzz/install/include/testlib.h
