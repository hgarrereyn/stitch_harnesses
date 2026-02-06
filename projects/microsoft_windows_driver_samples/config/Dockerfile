ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    printf '%s\n' \
    '#ifndef WDS_SAMPLE_H' \
    '#define WDS_SAMPLE_H' \
    '#ifdef __cplusplus' \
    'extern "C" {' \
    '#endif' \
    'int wds_echo_sum(const unsigned char* data, int len);' \
    'const char* wds_hello(void);' \
    '#ifdef __cplusplus' \
    '}' \
    '#endif' \
    '#endif' \
    > /fuzz/build/wds_sample.h && \
    printf '%s\n' \
    '#include <stddef.h>' \
    '#include "wds_sample.h"' \
    'int wds_echo_sum(const unsigned char* data, int len) {' \
    '    if (!data || len <= 0) return 0;' \
    '    int s = 0;' \
    '    for (int i = 0; i < len; ++i) s += (int)data[i];' \
    '    return s;' \
    '}' \
    'const char* wds_hello(void) {' \
    '    return "windows-driver-samples shim";' \
    '}' \
    > /fuzz/build/wds_sample.c && \
    ${CC} -fPIC -O2 -c /fuzz/build/wds_sample.c -o /fuzz/build/wds_sample.o && \
    ar rcs /fuzz/install/lib/libwds_sample.a /fuzz/build/wds_sample.o && \
    cp /fuzz/build/wds_sample.h /fuzz/install/include/
