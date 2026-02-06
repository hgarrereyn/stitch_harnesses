ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies needed; build and install a tiny static lib from the single-header qoi.h

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Install header and build a static library implementation
RUN set -eux; \
    install -d "$PREFIX/include" "$PREFIX/lib"; \
    cp qoi.h "$PREFIX/include/"; \
    echo '#define QOI_IMPLEMENTATION\n#include "qoi.h"' > qoi.c; \
    $CC -O2 -c qoi.c -I"$PREFIX/include" -o qoi.o; \
    ar rcs libqoi.a qoi.o; \
    ranlib libqoi.a || true; \
    mv libqoi.a "$PREFIX/lib/"; \
    rm -f qoi.c qoi.o
