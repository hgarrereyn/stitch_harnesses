ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; mkdir -p "$PREFIX"/include "$PREFIX"/lib /tmp/build

RUN cat <<'EOF' > /tmp/build/BlackHole.h
#ifndef BLACKHOLE_SHIM_H
#define BLACKHOLE_SHIM_H
#ifdef __cplusplus
extern "C" {
#endif
int BlackHole_Version(void);
#ifdef __cplusplus
}
#endif
#endif
EOF

RUN cat <<'EOF' > /tmp/build/blackhole_shim.c
#include "BlackHole.h"
int BlackHole_Version(void) { return 1; }
EOF

RUN set -eux; \
    stitch_libafl_cc -c -O2 -fPIC /tmp/build/blackhole_shim.c -o /tmp/build/blackhole_shim.o; \
    ar rcs /tmp/build/libblackhole.a /tmp/build/blackhole_shim.o; \
    ranlib /tmp/build/libblackhole.a; \
    cp /tmp/build/libblackhole.a "$PREFIX"/lib/; \
    cp /tmp/build/BlackHole.h "$PREFIX"/include/
