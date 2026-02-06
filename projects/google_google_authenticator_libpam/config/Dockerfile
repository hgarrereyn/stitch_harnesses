ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the project's reusable C sources
# and install headers and library to /fuzz/install
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    # Provide a minimal config.h so sources that include it can compile
    # (we don't need any specific feature defines for this subset)
    : > /fuzz/src/config.h; \
    cd /fuzz/src; \
    CC=stitch_libafl_cc; \
    $CC -O2 -g -c src/base32.c -I/fuzz/src/src -I/fuzz/src; \
    $CC -O2 -g -c src/sha1.c   -I/fuzz/src/src -I/fuzz/src; \
    $CC -O2 -g -c src/util.c   -I/fuzz/src/src -I/fuzz/src; \
    $CC -O2 -g -c src/hmac.c   -I/fuzz/src/src -I/fuzz/src; \
    ar rcs /fuzz/install/lib/libgoogleauth.a base32.o sha1.o util.o hmac.o; \
    cp src/base32.h src/hmac.h src/sha1.h /fuzz/install/include

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
