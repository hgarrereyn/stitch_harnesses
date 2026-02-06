ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a tiny static library from tools/lib using the kernel repo's userspace-friendly headers
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/linux; \
    cd /fuzz/build; \
    stitch_libafl_cc -O2 -fPIC -I/fuzz/src/tools/include -c /fuzz/src/tools/lib/zalloc.c -o zalloc.o; \
    ar rcs liblinux-tools.a zalloc.o; \
    cp liblinux-tools.a /fuzz/install/lib/; \
    cp /fuzz/src/tools/include/linux/zalloc.h /fuzz/install/include/linux/
