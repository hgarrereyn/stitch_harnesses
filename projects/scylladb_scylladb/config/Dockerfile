ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra deps needed; install the header-only subset as our "library"
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/cartesian_product.hh /fuzz/install/include/

RUN mkdir -p /fuzz/install/lib && true
