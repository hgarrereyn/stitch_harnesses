ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from ttyd's utils to provide a stable API for fuzzing
# We avoid full project deps (libwebsockets/libuv) and only build utils.c
RUN set -eux; \
    install -d /fuzz/install/include/ttyd /fuzz/install/lib; \
    install -m 0644 /fuzz/src/src/utils.h /fuzz/install/include/ttyd/utils.h; \
    gf_libafl_cc -O2 -fPIC -c /fuzz/src/src/utils.c -o /tmp/utils.o; \
    ar rcs /fuzz/install/lib/libttyd.a /tmp/utils.o; \
    ranlib /fuzz/install/lib/libttyd.a; \
    nm -g --defined-only /fuzz/install/lib/libttyd.a | head -n 20 || true
