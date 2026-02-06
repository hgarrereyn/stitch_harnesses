ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none strictly required). We'll use existing toolchain.
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp /fuzz/src/oepl-proto.h /fuzz/install/include/ \
    && cp /fuzz/src/oepl-esp-ap-proto.h /fuzz/install/include/ \
    && cp /fuzz/src/oepl-definitions.h /fuzz/install/include/ \
    && cp /fuzz/src/tag_types.h /fuzz/install/include/ \
    && echo "int openepaperlink_dummy(void){return 0;}" > /tmp/dummy.c \
    && stitch_libafl_cc -c -O2 /tmp/dummy.c -o /tmp/dummy.o \
    && ar rcs /fuzz/install/lib/libopenepaperlink.a /tmp/dummy.o \
    && rm -f /tmp/dummy.c /tmp/dummy.o
