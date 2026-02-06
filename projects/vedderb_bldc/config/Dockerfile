ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build; \
    # Build static library from portable utility sources only
    $CC -O2 -fPIC -I/fuzz/src/util -c /fuzz/src/util/buffer.c -o /tmp/build/buffer.o; \
    $CC -O2 -fPIC -I/fuzz/src/util -c /fuzz/src/util/digital_filter.c -o /tmp/build/digital_filter.o; \
    $CC -O2 -fPIC -I/fuzz/src/util -c /fuzz/src/util/utils_math.c -o /tmp/build/utils_math.o; \
    $CC -O2 -fPIC -I/fuzz/src/util/lzo -I/fuzz/src/util -c /fuzz/src/util/lzo/minilzo.c -o /tmp/build/minilzo.o; \
    ar rcs /fuzz/install/lib/libbldcutils.a /tmp/build/buffer.o /tmp/build/digital_filter.o /tmp/build/utils_math.o /tmp/build/minilzo.o; \
    # Install headers
    cp /fuzz/src/util/buffer.h /fuzz/install/include/; \
    cp /fuzz/src/util/digital_filter.h /fuzz/install/include/; \
    cp /fuzz/src/util/utils_math.h /fuzz/install/include/; \
    cp /fuzz/src/util/lzo/*.h /fuzz/install/include/;
