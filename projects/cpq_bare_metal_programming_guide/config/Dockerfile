ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install step: create a tiny static library and install public headers
# The project is a guide with example headers; we expose a minimal API header
# and a stub static library for linking.
RUN set -eux; \
    mkdir -p /fuzz/install/include/baremetal /fuzz/install/lib; \
    cp /fuzz/src/steps/step-4-printf/hal.h /fuzz/install/include/baremetal/hal.h; \
    echo 'void bm_dummy(void){}' > /tmp/dummy.c; \
    gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs /fuzz/install/lib/libbaremetal.a /tmp/dummy.o; \
    rm -f /tmp/dummy.c /tmp/dummy.o
