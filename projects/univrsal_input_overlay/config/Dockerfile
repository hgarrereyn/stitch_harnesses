ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include/json ${PREFIX}/lib && \
    ${CXX} -O2 -I/fuzz/src/deps/json11 -c /fuzz/src/deps/json11/json11.cpp -o /tmp/json11.o && \
    ar rcs ${PREFIX}/lib/libjson11.a /tmp/json11.o && \
    ranlib ${PREFIX}/lib/libjson11.a && \
    cp /fuzz/src/deps/json11/json/json11.hpp ${PREFIX}/include/json/
