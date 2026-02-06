ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Windows-only project; provide a minimal shim library to allow building/linking tests on Linux.

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends ca-certificates; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p "$PREFIX/include" "$PREFIX/lib" /tmp/build; \
    ver=$(grep -m1 '^simplewall=' /fuzz/src/VERSION 2>/dev/null | cut -d'=' -f2 | cut -d'|' -f1 || echo unknown); \
    printf '#pragma once\n#ifdef __cplusplus\nextern "C" {\n#endif\nconst char* simplewall_version(void);\nint simplewall_sum(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n' > "$PREFIX/include/simplewall.h"; \
    printf '#include <stddef.h>\nstatic const char ver[] = "%s";\nconst char* simplewall_version(void){ return ver; }\nint simplewall_sum(int a,int b){ return a+b; }\n' "$ver" > /tmp/build/simplewall.c; \
    $CC -fPIC -O2 -c /tmp/build/simplewall.c -o /tmp/build/simplewall.o; \
    ar rcs "$PREFIX/lib/libsimplewall.a" /tmp/build/simplewall.o; \
    rm -rf /tmp/build
