ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: place selected public headers into /fuzz/install/include
RUN set -eux; \
    mkdir -p /fuzz/install/include/common/base; \
    cp -v /fuzz/src/src/common/base/MurmurHash2.h /fuzz/install/include/common/base/

# No build needed; headers are header-only and require no external deps
