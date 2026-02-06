ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: no extra system dependencies required

# Install step: copy headers into /fuzz/install/include
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/include/obfus.h /fuzz/install/include/

# No library to build; header-only
