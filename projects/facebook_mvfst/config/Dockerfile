ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: provide headers in /fuzz/install so consumers can include mvfst API.
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/quic && \
    mkdir -p /fuzz/install/include/quic/api && \
    # Install core public headers
    cp -v quic/QuicConstants.h quic/QuicTypealiases.h quic/QuicException.h quic/QuicTLSException.h quic/mvfst-config.h /fuzz/install/include/quic/ || true && \
    # Install API headers (excluding tests)
    find quic/api -type f -name '*.h' ! -path '*/test/*' -exec bash -lc 'd=$(dirname {}); sub=${d#quic/api/}; mkdir -p /fuzz/install/include/quic/api/$sub; cp -v {} /fuzz/install/include/quic/api/$sub/' \; || true && \
    true

# Create lib dir for potential linkage by downstream builds
RUN mkdir -p /fuzz/install/lib
