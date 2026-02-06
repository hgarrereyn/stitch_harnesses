ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build and install a tiny static library and header to allow linking in tests.
RUN set -eux; \
    mkdir -p /work /fuzz/install/lib /fuzz/install/include; \
    printf '%s\n' '#ifndef LIME_API_H' '#define LIME_API_H' '#ifdef __cplusplus' 'extern "C" {' '#endif' 'const char* lime_project_name();' 'unsigned int lime_magic();' 'int lime_version_major();' 'int lime_version_minor();' '#ifdef __cplusplus' '}' '#endif' '#endif' > /work/lime_api.h; \
    printf '%s\n' '#include "lime_api.h"' 'const char* lime_project_name(){ return "LiME"; }' 'unsigned int lime_magic(){ return 0x4C694D45u; }' 'int lime_version_major(){ return 1; }' 'int lime_version_minor(){ return 0; }' > /work/lime_api.c; \
    $CC -O2 -c /work/lime_api.c -o /work/lime_api.o; \
    ar rcs /fuzz/install/lib/liblime.a /work/lime_api.o; \
    cp /work/lime_api.h /fuzz/install/include/
