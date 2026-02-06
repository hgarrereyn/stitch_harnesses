ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools (none needed); create install prefix and copy headers; build a tiny static stub lib
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX/include/helix" "$PREFIX/lib"; \
    cp -r /fuzz/src/hel/include/*.h "$PREFIX/include/"; \
    # still copy helix headers for completeness, though not used by codegen
    cp -r /fuzz/src/hel/include/helix/*.hpp "$PREFIX/include/helix/" || true; \
    printf "int __helix_stub_dummy(void){return 0;}" > /tmp/helix_stub.c; \
    $CC -c -O2 -fPIC -I"$PREFIX/include" /tmp/helix_stub.c -o /tmp/helix_stub.o; \
    ar rcs "$PREFIX/lib/libhelixstub.a" /tmp/helix_stub.o; \
    rm -f /tmp/helix_stub.c /tmp/helix_stub.o
