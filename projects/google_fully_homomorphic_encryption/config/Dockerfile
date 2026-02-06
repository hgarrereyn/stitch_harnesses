ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are required for building a tiny static lib
# from the repository sources.

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX"/include/transpiler/data "$PREFIX"/lib; \
    cd /fuzz/src/transpiler/data; \
    "$CXX" -c -O2 -fPIC primitives.cc -I. -o primitives.o; \
    ar rcs libfhedata.a primitives.o; \
    cp -v primitives.h "$PREFIX"/include/transpiler/data/; \
    cp -v libfhedata.a "$PREFIX"/lib/
