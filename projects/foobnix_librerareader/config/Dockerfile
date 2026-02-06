ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

WORKDIR /fuzz/src/Builder/jni/libhqx-1.2
RUN mkdir -p /fuzz/build/hqx /fuzz/install/lib /fuzz/install/include && \
    "$CC" -O2 -fPIC -c hq2x.c -o /fuzz/build/hqx/hq2x.o && \
    "$CC" -O2 -fPIC -c hq3x.c -o /fuzz/build/hqx/hq3x.o && \
    "$CC" -O2 -fPIC -c hq4x.c -o /fuzz/build/hqx/hq4x.o && \
    "$CC" -O2 -fPIC -c init.c -o /fuzz/build/hqx/init.o && \
    ar rcs /fuzz/install/lib/libhqx.a /fuzz/build/hqx/*.o && \
    cp hqx.h /fuzz/install/include/
