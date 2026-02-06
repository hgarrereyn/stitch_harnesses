ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install header-only library into /fuzz/install
RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp /fuzz/src/src/raygui.h /fuzz/install/include/
