ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external system dependencies are required; this is a header-only style Arduino library.
# We just install headers into /fuzz/install/include so external code can include them.

# Environment and paths
ENV PREFIX=/fuzz/install

# Copy and "install" headers
RUN mkdir -p ${PREFIX}/include && \
    cp -v /fuzz/src/src/IRVersion.h ${PREFIX}/include/ && \
    cp -v /fuzz/src/src/IRProtocol.h ${PREFIX}/include/ && \
    cp -v /fuzz/src/src/LongUnion.h ${PREFIX}/include/

# Provide lib directory even if empty (no linking needed)
RUN mkdir -p ${PREFIX}/lib
