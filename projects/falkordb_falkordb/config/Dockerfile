ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Create a tiny shim library implementing a small subset of the public API
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include /tmp/build; \
    cat > /tmp/build/minival.c <<'EOF'
#include "value.h"
SIValue SI_LongVal(int64_t i){ SIValue v; v.longval=i; v.type=T_INT64; v.allocation=M_NONE; return v;}
SIValue SI_DoubleVal(double d){ SIValue v; v.doubleval=d; v.type=T_DOUBLE; v.allocation=M_NONE; return v;}
SIValue SI_NullVal(void){ SIValue v; v.longval=0; v.type=T_NULL; v.allocation=M_NONE; return v;}
SIValue SI_BoolVal(int b){ SIValue v; v.longval=b; v.type=T_BOOL; v.allocation=M_NONE; return v;}
SIValue SI_PtrVal(void *p){ SIValue v; v.ptrval=p; v.type=T_PTR; v.allocation=M_NONE; return v;}
EOF

# Build and install the static library and headers
RUN set -eux; \
    gf_libafl_cc -fPIC -I./src -Ideps/xxHash -c /tmp/build/minival.c -o /tmp/build/minival.o; \
    ar rcs ${PREFIX}/lib/libfalkordb.a /tmp/build/minival.o; \
    cp src/redismodule.h ${PREFIX}/include/; \
    cp src/RG.h ${PREFIX}/include/; \
    cp src/value.h ${PREFIX}/include/; \
    cp deps/xxHash/xxhash.h ${PREFIX}/include/
