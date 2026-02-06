ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No build system; headers-only. Just install headers to /fuzz/install/include
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -v /fuzz/src/cute_*.h /fuzz/install/include/

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install
