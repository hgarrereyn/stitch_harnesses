ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the simple compression static library from the repo
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Build static lib from bdk/libs/compr and install headers
RUN set -eux; \
    mkdir -p /fuzz/build/shim/include/mem; \
    printf "#ifndef MEM_HEAP_H\n#define MEM_HEAP_H\n#include <stdlib.h>\n#include <string.h>\n#include <stdint.h>\n#ifndef likely\n#define likely(x)   (__builtin_expect(!!(x), 1))\n#endif\n#ifndef unlikely\n#define unlikely(x) (__builtin_expect(!!(x), 0))\n#endif\ntypedef unsigned char BYTE;\nstatic inline void* zalloc(size_t n){ void* p = malloc(n); if(p) memset(p,0,n); return p; }\n#endif\n" > /fuzz/build/shim/include/mem/heap.h; \
    mkdir -p /fuzz/build "$INSTALL_PREFIX/lib" "$INSTALL_PREFIX/include" "$INSTALL_PREFIX/include/utils"; \
    cd bdk/libs/compr; \
    for f in lz4.c lz.c blz.c; do \
      gf_libafl_cc -O2 -fPIC -c "$f" -I/fuzz/build/shim/include -I. -I/fuzz/src/bdk -o "/fuzz/build/$(basename "$f" .c).o"; \
    done; \
    ar rcs "$INSTALL_PREFIX/lib/libhekatecompr.a" /fuzz/build/*.o; \
    cp lz4.h lz.h blz.h "$INSTALL_PREFIX/include/"; \
    cp /fuzz/src/bdk/utils/types.h "$INSTALL_PREFIX/include/utils/types.h"; \
    echo "Installed libhekatecompr.a and headers to $INSTALL_PREFIX"
