ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# The project contains only public headers; no build is required.
# We just install headers into /fuzz/install so clients can include them.

RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -v /fuzz/src/libraries/include/* /fuzz/install/include/
