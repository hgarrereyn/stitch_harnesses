ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library: just install headers to /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/include/atomic_queue /fuzz/install/include/
