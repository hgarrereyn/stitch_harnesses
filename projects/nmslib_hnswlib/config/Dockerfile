ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: just install headers to /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/hnswlib /fuzz/install/include/
