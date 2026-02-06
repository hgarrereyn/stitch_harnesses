ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build utilities
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      ca-certificates \
      build-essential \
      pkg-config \
      python3; \
    rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include/sunshine ${PREFIX}/lib ${PREFIX}/share

# Install a subset of headers that form a usable public API for basic utilities
RUN cp /fuzz/src/src/utility.h ${PREFIX}/include/sunshine/utility.h && \
    cp /fuzz/src/src/uuid.h ${PREFIX}/include/sunshine/uuid.h

# Build a tiny dummy static library with the required compilers
RUN set -eux; \
    echo "int sunshine_dummy_symbol() { return 0; }" > /tmp/sunshine_dummy.c; \
    stitch_libafl_cc -c /tmp/sunshine_dummy.c -o /tmp/sunshine_dummy.o; \
    ar rcs ${PREFIX}/lib/libsunshine.a /tmp/sunshine_dummy.o; \
    ranlib ${PREFIX}/lib/libsunshine.a; \
    rm -f /tmp/sunshine_dummy.c /tmp/sunshine_dummy.o
