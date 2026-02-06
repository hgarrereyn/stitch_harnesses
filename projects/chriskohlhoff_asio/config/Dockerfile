ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Asio is header-only when ASIO_HEADER_ONLY is defined. We just need to install headers.
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -r /fuzz/src/include/* /fuzz/install/include/

# Environment for builds
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install