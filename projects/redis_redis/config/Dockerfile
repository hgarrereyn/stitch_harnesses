ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

WORKDIR /fuzz/src/deps/hiredis
RUN make -j"$(nproc)" static && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/hiredis && \
    cp libhiredis.a ${PREFIX}/lib/ && \
    cp hiredis.h async.h read.h sds.h alloc.h fmacros.h net.h sockcompat.h win32.h sdsalloc.h sdscompat.h dict.h hiredis_ssl.h ${PREFIX}/include/hiredis/
