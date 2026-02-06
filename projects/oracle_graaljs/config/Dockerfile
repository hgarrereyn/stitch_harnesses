ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools for creating a static library
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# Create a minimal C static library and install selected public headers from graal-nodejs
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/include/graalnode ${INSTALL_PREFIX}/lib; \
    # Install a small, stable public header with version macros
    cp /fuzz/src/graal-nodejs/src/node_version.h ${INSTALL_PREFIX}/include/graalnode/; \
    # Build a tiny dummy static library so linkers have a target archive
    echo 'void __graalnode_dummy(void){}' > /tmp/dummy.c; \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs ${INSTALL_PREFIX}/lib/libgraalnode.a /tmp/dummy.o; \
    rm -f /tmp/dummy.c /tmp/dummy.o
