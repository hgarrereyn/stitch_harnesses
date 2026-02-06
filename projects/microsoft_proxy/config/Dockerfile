ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: just install headers into /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/include/* /fuzz/install/include/
