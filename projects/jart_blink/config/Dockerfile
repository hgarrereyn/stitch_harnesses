ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx ./configure && \
    make -j"$(nproc)" MODE=rel o/rel/blink/blink.a && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/blink && \
    cp o/rel/blink/blink.a /fuzz/install/lib/libblink.a && \
    cp blink/*.h /fuzz/install/include/blink/ && \
    cp config.h /fuzz/install/include/
