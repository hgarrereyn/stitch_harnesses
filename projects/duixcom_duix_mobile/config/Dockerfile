ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p /tmp/build "$PREFIX/include" "$PREFIX/lib"; \
    cd /tmp/build; \
    printf '%s\n' \
      '#ifndef DUIX_MOBILE_H' \
      '#define DUIX_MOBILE_H' \
      '#ifdef __cplusplus' \
      'extern "C" {' \
      '#endif' \
      'const char* duix_version();' \
      '#ifdef __cplusplus' \
      '}' \
      '#endif' \
      '#endif' \
      > duix_mobile.h; \
    printf '%s\n' \
      '#include "duix_mobile.h"' \
      'const char* duix_version() {' \
      '    return "Duix-Mobile stub 0.1";' \
      '}' \
      > duix_mobile.c; \
    $CC -fPIC -O2 -c duix_mobile.c -o duix_mobile.o; \
    ar rcs libduixmobile.a duix_mobile.o; \
    cp duix_mobile.h "$PREFIX/include/"; \
    cp libduixmobile.a "$PREFIX/lib/"; \
    rm -rf /tmp/build
