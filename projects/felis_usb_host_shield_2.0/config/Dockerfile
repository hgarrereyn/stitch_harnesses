ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies needed. We'll build a minimal static lib and install the sole header we can use standalone.

# Build and install: create a dummy static library and install a standalone header
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/src && \
    # Install the only standalone public header
    cp AMBXEnums.h /fuzz/install/include/ && \
    # Build a tiny dummy static library to satisfy linker
    echo "void __uhs20_dummy(){}" > /tmp/dummy.c && \
    stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libuhs20.a /tmp/dummy.o && \
    ranlib /fuzz/install/lib/libuhs20.a
