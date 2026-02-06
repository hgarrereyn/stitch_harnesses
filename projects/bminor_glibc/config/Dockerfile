ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install the public argp header from glibc. We rely on the system libc for implementation.
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp /fuzz/src/argp/argp.h /fuzz/install/include/
