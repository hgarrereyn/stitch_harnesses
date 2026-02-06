ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/hwbuild
RUN printf '%s\n' '#ifndef HW_H' '#define HW_H' '#ifdef __cplusplus' 'extern "C" {' '#endif' 'const char* hw_name(void);' 'int hw_sum(int a, int b);' '#ifdef __cplusplus' '}' '#endif' '#endif' > /tmp/hwbuild/hw.h
RUN printf '%s\n' '#include "hw.h"' 'const char* hw_name(void) { return "Hacking-Windows"; }' 'int hw_sum(int a, int b) { return a + b; }' > /tmp/hwbuild/hw.c
RUN set -eux; \
    ${CC} -O2 -fPIC -c /tmp/hwbuild/hw.c -o /tmp/hwbuild/hw.o; \
    ar rcs /tmp/hwbuild/libhw.a /tmp/hwbuild/hw.o; \
    cp /tmp/hwbuild/libhw.a ${PREFIX}/lib/; \
    cp /tmp/hwbuild/hw.h ${PREFIX}/include/
