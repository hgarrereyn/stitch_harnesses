ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libx11-dev libxrandr-dev libgl1-mesa-dev libxcursor-dev libxext-dev libxi-dev \
    ca-certificates pkg-config file && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRCDIR=/fuzz/src
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/rgfw-build && \
    printf "#define RGFW_IMPLEMENTATION\n#define RGFW_EXPORT\n#include \"RGFW.h\"\n" > /tmp/rgfw-build/rgfw.c && \
    ${CC} -O2 -fPIC -I${SRCDIR} -c /tmp/rgfw-build/rgfw.c -o /tmp/rgfw-build/rgfw.o && \
    ar rcs /tmp/rgfw-build/librgfw.a /tmp/rgfw-build/rgfw.o && \
    install -m 0644 ${SRCDIR}/RGFW.h ${PREFIX}/include/RGFW.h && \
    install -m 0644 ${SRCDIR}/XDL.h ${PREFIX}/include/XDL.h && \
    install -m 0644 /tmp/rgfw-build/librgfw.a ${PREFIX}/lib/librgfw.a && \
    rm -rf /tmp/rgfw-build
