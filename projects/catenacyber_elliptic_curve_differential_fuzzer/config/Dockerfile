ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to build a static archive
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Build a tiny static library that exposes a small, dependency-free API derived from the project
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include \
    && printf "#include <stddef.h>\n#include <stdint.h>\nsize_t ecdf_bitlen_from_tls_id(uint16_t tlsid){\n switch(tlsid){case 18:case 19:return 192;case 20:case 21:return 224;case 22:case 23:case 26:return 256;case 24:case 27:return 384;case 25:return 521;case 28:return 512;}return 0;}\n" > ec_api.c \
    && $CC -O2 -fPIC -c ec_api.c -o ec_api.o \
    && ar rcs ${PREFIX}/lib/libecfuzzer.a ec_api.o \
    && cp fuzz_ec.h ${PREFIX}/include/
