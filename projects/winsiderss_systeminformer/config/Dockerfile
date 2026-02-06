ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a portable static library from the repo: xxhash (vendored under tools/thirdparty/xxhash)
# We build libsi_xxhash.a and install header xxhash.h under /fuzz/install/include
RUN set -eux; \
    mkdir -p /fuzz/build/xxhash /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src/tools/thirdparty/xxhash; \
    stitch_libafl_cc -O2 -I. -c xxhash.c -o /fuzz/build/xxhash/xxhash.o; \
    ar rcs /fuzz/install/lib/libsi_xxhash.a /fuzz/build/xxhash/xxhash.o; \
    cp /fuzz/src/tools/thirdparty/xxhash/xxhash.h /fuzz/install/include/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
ENV CFLAGS="-O2" CXXFLAGS="-O2"
