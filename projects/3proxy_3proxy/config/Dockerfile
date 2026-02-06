ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from 3proxy sources and install headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV DESTDIR=/fuzz/install

# Build with fuzzing compilers
WORKDIR /fuzz/src
RUN mkdir -p ${DESTDIR}/include ${DESTDIR}/lib && \
    # Install public headers
    cp src/version.h ${DESTDIR}/include/ && \
    cp src/structures.h ${DESTDIR}/include/ && \
    cp src/proxy.h ${DESTDIR}/include/ && \
    # Build a minimal static library exposing some utility APIs (base64)
    stitch_libafl_cc -DNOODBC -fPIC -O2 -c src/base64.c -o /tmp/base64.o && \
    ar rcs ${DESTDIR}/lib/lib3proxy.a /tmp/base64.o && \
    ranlib ${DESTDIR}/lib/lib3proxy.a
