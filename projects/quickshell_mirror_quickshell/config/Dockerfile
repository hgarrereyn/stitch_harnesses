ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No heavy deps needed; build a minimal static library interface for testing
# using the required compilers and install into /fuzz/install.

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/build; \
    cat > /fuzz/install/include/quickshell_stub.hpp <<'EOF'
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
int qs_add(int a, int b);
#ifdef __cplusplus
}
#endif
EOF

RUN set -eux; \
    cat > /tmp/build/qsstub.c <<'EOF'
#include <stddef.h>
int qs_add(int a, int b) { return a + b; }
EOF

RUN set -eux; \
    gf_libafl_cc -O2 -fPIC -c /tmp/build/qsstub.c -o /tmp/build/qsstub.o; \
    ar rcs /fuzz/install/lib/libquickshell.a /tmp/build/qsstub.o; \
    ranlib /fuzz/install/lib/libquickshell.a; \
    echo 'Installed stub static library at /fuzz/install/lib/libquickshell.a';
