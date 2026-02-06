ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external build is required as the repository contains only example applications
# that depend on a preinstalled ONNX Runtime. For the purpose of fuzzing headers/API,
# we install the available public headers so they can be included by fuzz targets.

# Ensure fuzzing wrappers are the default compilers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Create install prefix and copy headers
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/c_cxx/include/* /fuzz/install/include/
