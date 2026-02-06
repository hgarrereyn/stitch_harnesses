ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: install headers into /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/CImg.h /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/plugins && \
    cp -vr /fuzz/src/plugins/* /fuzz/install/include/plugins/

# Environment for compilers (used by later build steps outside this Dockerfile)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
