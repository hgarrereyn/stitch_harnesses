ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends zlib1g-dev ca-certificates make binutils && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Install headers and create a small static library from non-zlib-dependent routines
RUN set -eux; \
    mkdir -p /fuzz/install/include/pure /fuzz/install/lib; \
    cp -v /fuzz/src/src/PureLib/pure/*.h /fuzz/install/include/pure/; \
    printf '#include <stdint.h>\n#include <assert.h>\n#include <string.h>\n#include <stdlib.h>\n#include <stdio.h>\n#include "pure/pure_constants.h"\n#include "pure/pure_errors.h"\n#include "pure/pure_signatures.h"\n#include "pure/pure_routines.h"\nint purelib_dummy(void){return 0;}\n' > /tmp/purelib.c; \
    "$CC" -O2 -fPIC -I/fuzz/install/include -c /tmp/purelib.c -o /tmp/purelib.o; \
    ar rcs /fuzz/install/lib/libpure.a /tmp/purelib.o; \
    rm -f /tmp/purelib.c /tmp/purelib.o
