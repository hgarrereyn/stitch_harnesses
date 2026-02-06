ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install headers for building against Cuberite sources and vendored third-party headers used by Globals.h
RUN mkdir -p /fuzz/install/include/cuberite && \
    cp -r /fuzz/src/src/* /fuzz/install/include/cuberite/ && \
    mkdir -p /fuzz/install/include/fmt && \
    cp -r /fuzz/src/lib/fmt/include/* /fuzz/install/include/
