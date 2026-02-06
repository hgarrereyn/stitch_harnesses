ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install zopfli as a static library into /fuzz/install
WORKDIR /fuzz/src

RUN mkdir -p /fuzz/install/lib /fuzz/install/include /tmp/build \
 && cd /tmp/build \
 && stitch_libafl_cc -O2 -W -Wall -Wextra -Wno-unused-function -DNDEBUG -c \
    /fuzz/src/src/zopfli/blocksplitter.c \
    /fuzz/src/src/zopfli/cache.c \
    /fuzz/src/src/zopfli/deflate.c \
    /fuzz/src/src/zopfli/gzip_container.c \
    /fuzz/src/src/zopfli/hash.c \
    /fuzz/src/src/zopfli/katajainen.c \
    /fuzz/src/src/zopfli/lz77.c \
    /fuzz/src/src/zopfli/squeeze.c \
    /fuzz/src/src/zopfli/tree.c \
    /fuzz/src/src/zopfli/util.c \
    /fuzz/src/src/zopfli/zlib_container.c \
    /fuzz/src/src/zopfli/zopfli_lib.c \
 && ar rcs /fuzz/install/lib/libzopfli.a *.o \
 && cp -v /fuzz/src/src/zopfli/zopfli.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/zopfli/gzip_container.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/zopfli/zlib_container.h /fuzz/install/include/

