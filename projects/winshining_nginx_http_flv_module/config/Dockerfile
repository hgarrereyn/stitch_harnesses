ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix and install headers (header-only exposure for codegen/testing)
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/*.h /fuzz/install/include/ || true
