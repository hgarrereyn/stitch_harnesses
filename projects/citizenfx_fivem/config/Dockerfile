ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a tiny static lib
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build and install a small static library from the project's shared base64 implementation
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include /tmp/build && \
    cd /tmp/build && \
    ${CXX} -O2 -fPIC -c ${SRC}/code/shared/base64.cpp -I${SRC}/code/shared -o base64.o && \
    ar rcs libfivem_base64.a base64.o && \
    cp libfivem_base64.a ${PREFIX}/lib/ && \
    cp ${SRC}/code/shared/base64.h ${PREFIX}/include/ && \
    cd / && rm -rf /tmp/build
