ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (for ar) and set compilers
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build static library from the vendored sources
WORKDIR /fuzz/src

# Create install dirs
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build

# Compile C sources
RUN $CC -fPIC -O2 -Isrc/ujson/lib -c src/ujson/lib/ultrajsonenc.c -o /tmp/build/ultrajsonenc.o && \
    $CC -fPIC -O2 -Isrc/ujson/lib -c src/ujson/lib/ultrajsondec.c -o /tmp/build/ultrajsondec.o

# Compile double-conversion and wrapper C++ sources
RUN DC_INC=src/ujson/deps/double-conversion/double-conversion && \
    $CXX -fPIC -O2 -Isrc/ujson/lib -I"$DC_INC" -c src/ujson/lib/dconv_wrapper.cc -o /tmp/build/dconv_wrapper.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/bignum-dtoa.cc -o /tmp/build/dc_bignum-dtoa.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/bignum.cc -o /tmp/build/dc_bignum.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/cached-powers.cc -o /tmp/build/dc_cached-powers.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/double-to-string.cc -o /tmp/build/dc_double-to-string.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/fast-dtoa.cc -o /tmp/build/dc_fast-dtoa.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/fixed-dtoa.cc -o /tmp/build/dc_fixed-dtoa.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/string-to-double.cc -o /tmp/build/dc_string-to-double.o && \
    $CXX -fPIC -O2 -I"$DC_INC" -c $DC_INC/strtod.cc -o /tmp/build/dc_strtod.o

# Archive into a single static library and install headers
RUN ar rcs /fuzz/install/lib/libujson.a /tmp/build/*.o && \
    cp src/ujson/lib/ultrajson.h /fuzz/install/include/

