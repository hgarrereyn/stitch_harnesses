ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are required to build the standalone bitmask library.

# Build and install a static libbitmask from pygame's bundled bitmask sources
RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/build; \
    cp /fuzz/src/src_c/include/bitmask.h /fuzz/install/include/; \
    cd /tmp/build; \
    gf_libafl_cc -O2 -c /fuzz/src/src_c/bitmask.c -I/fuzz/install/include -o bitmask.o; \
    ar rcs libbitmask.a bitmask.o; \
    ranlib libbitmask.a || true; \
    cp libbitmask.a /fuzz/install/lib/; \
    rm -rf /tmp/build
