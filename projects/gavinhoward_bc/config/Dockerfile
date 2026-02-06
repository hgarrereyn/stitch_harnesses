ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends python3 ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

RUN ./configure.sh --library --prefix=${PREFIX} && \
    make -j"$(nproc)" && \
    make install

RUN test -f /fuzz/install/lib/libbcl.a && test -f /fuzz/install/include/bcl.h
