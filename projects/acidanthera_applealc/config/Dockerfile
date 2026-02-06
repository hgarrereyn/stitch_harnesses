ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library and install public headers to satisfy linking
# AppleALC is a macOS kernel extension and cannot be built on Linux. We install
# the small shared user/kernel header and create a dummy static library to link against.

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp /fuzz/src/AppleALC/UserKernelShared.h /fuzz/install/include/; \
    echo 'void applealc_dummy(void){}' > /tmp/dummy.c; \
    gf_libafl_cc -fPIC -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs /fuzz/install/lib/libapplealc.a /tmp/dummy.o; \
    ranlib /fuzz/install/lib/libapplealc.a; \
    rm -f /tmp/dummy.c /tmp/dummy.o
