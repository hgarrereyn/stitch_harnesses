ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: we only need to provide headers for a header-only part of the library
# and set up an install prefix. No library linking is required for the chosen API.

RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cd /fuzz/src; \
    # Install headers (preserve directory structure for includes)
    mkdir -p /fuzz/install/include/verible/common/strings; \
    cp -a verible/common/strings/compare.h /fuzz/install/include/verible/common/strings/

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
