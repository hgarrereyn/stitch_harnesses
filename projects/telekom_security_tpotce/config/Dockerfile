ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends make ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/build; \
    cp /fuzz/src/docker/p0f/api.h /fuzz/install/include/; \
    cp /fuzz/src/docker/p0f/types.h /fuzz/install/include/; \
    printf '%s\n' \
      '#include <stddef.h>' \
      '#ifdef __cplusplus' \
      'extern "C" {' \
      '#endif' \
      'const char* p0f_shim_version(void) { return "tpotce-p0fshim-1.0"; }' \
      '#ifdef __cplusplus' \
      '}' \
      '#endif' \
      > /tmp/build/p0fshim.c; \
    "$CC" -O2 -fPIC -c /tmp/build/p0fshim.c -o /tmp/build/p0fshim.o; \
    ar rcs /fuzz/install/lib/libp0fshim.a /tmp/build/p0fshim.o; \
    ranlib /fuzz/install/lib/libp0fshim.a; \
    rm -rf /tmp/build
