ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install step for header-only library: copy the header into /fuzz/install/include
RUN mkdir -p /fuzz/install/include && \
    cp /fuzz/src/httplib.h /fuzz/install/include/httplib.h
