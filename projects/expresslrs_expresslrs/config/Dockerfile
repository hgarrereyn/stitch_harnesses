ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create install prefix and build a minimal static library exposing header-only utilities
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/src/include/LowPassFilter.h /fuzz/install/include/ && \
    cp /fuzz/src/src/include/deferred.h /fuzz/install/include/ && \
    printf "void elrs_dummy(void){}" > /tmp/dummy.c && \
    gf_libafl_cc -O2 -fPIC -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libexpresslrs.a /tmp/dummy.o && \
    ranlib /fuzz/install/lib/libexpresslrs.a

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
