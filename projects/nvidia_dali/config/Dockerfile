ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: copy headers and create an empty static library to link against
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp -R /fuzz/src/include/* /fuzz/install/include/; \
    # Create an empty static library archive to satisfy linker
    echo "" > /tmp/empty.c; \
    gf_libafl_cc -c /tmp/empty.c -o /tmp/empty.o; \
    ar rcs /fuzz/install/lib/libdali.a /tmp/empty.o; \
    rm -f /tmp/empty.c /tmp/empty.o

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:$PKG_CONFIG_PATH
