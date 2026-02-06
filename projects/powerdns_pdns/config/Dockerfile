ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX/include/pdns" "$PREFIX/lib" /tmp/pdnsinc; \
    printf "#pragma once\n#define HAVE_CLOCK_GETTIME 1\n" > /tmp/pdnsinc/config.h; \
    cd /fuzz/src; \
    ${CXX} -O2 -fPIC -I/tmp/pdnsinc -c pdns/gettime.cc -o gettime.o; \
    ar rcs libpdns-gettime.a gettime.o; \
    ranlib libpdns-gettime.a || true; \
    install -m644 libpdns-gettime.a "$PREFIX/lib/"; \
    install -m644 pdns/gettime.hh "$PREFIX/include/pdns/"
