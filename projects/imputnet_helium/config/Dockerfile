ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include/helium ${PREFIX}/lib /tmp/heliumlib

RUN cat > /tmp/heliumlib/helium.h <<'EOF'
#ifndef HELIUM_HELIUM_H
#define HELIUM_HELIUM_H
#ifdef __cplusplus
extern "C" {
#endif
// Returns a constant string identifying the library.
const char* helium_hello(void);
// Returns the sum of two integers.
int helium_sum(int a, int b);
#ifdef __cplusplus
}
#endif
#endif // HELIUM_HELIUM_H
EOF

RUN cat > /tmp/heliumlib/helium.c <<'EOF'
#include "helium.h"
const char* helium_hello(void){
    return "Helium";
}
int helium_sum(int a, int b){
    return a + b;
}
EOF

RUN ${CC} -O2 -fPIC -c /tmp/heliumlib/helium.c -o /tmp/heliumlib/helium.o \
 && ar rcs ${PREFIX}/lib/libhelium.a /tmp/heliumlib/helium.o \
 && cp /tmp/heliumlib/helium.h ${PREFIX}/include/helium/
