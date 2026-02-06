ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Install headers and create a minimal static lib to satisfy linking
RUN mkdir -p /fuzz/install/include/velox/type /fuzz/install/lib/velox /tmp/build && \
    cp /fuzz/src/velox/type/Tree.h /fuzz/install/include/velox/type/ && \
    echo "int velox_placeholder_symbol() { return 42; }" > /tmp/build/placeholder.c && \
    ${CC} -c -O2 -fPIC /tmp/build/placeholder.c -o /tmp/build/placeholder.o && \
    ar rcs /fuzz/install/lib/velox/libvelox.a /tmp/build/placeholder.o && \
    rm -rf /tmp/build
