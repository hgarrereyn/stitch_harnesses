ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal, portable subset of NanaZip (vendored xxHash)
# into /fuzz/install as a static library.

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build; \
    # Build static xxHash library from the vendored source
    gf_libafl_cc -O2 -fPIC -c /fuzz/src/NanaZip.Codecs/xxHash/xxhash.c -o /tmp/build/xxhash.o; \
    ar rcs /fuzz/install/lib/libnanazip_xxhash.a /tmp/build/xxhash.o; \
    cp /fuzz/src/NanaZip.Codecs/xxHash/xxhash.h /fuzz/install/include/xxhash.h
