ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src
RUN CFLAGS="-O2 -fPIC -D__BLST_PORTABLE__" ./build.sh && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include && \
    cp libblst.a ${PREFIX}/lib/ && \
    cp bindings/blst.h bindings/blst_aux.h bindings/blst.hpp ${PREFIX}/include/
