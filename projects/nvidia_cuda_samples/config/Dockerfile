ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# No external deps required for the header-only subset we expose.
RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/Common/nvVector.h /fuzz/install/include/ && \
    cp /fuzz/src/Common/nvMatrix.h /fuzz/install/include/ && \
    cp /fuzz/src/Common/nvQuaternion.h /fuzz/install/include/
