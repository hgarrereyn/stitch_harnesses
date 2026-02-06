ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and prepare install prefix
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libassimp-dev \
 && rm -rf /var/lib/apt/lists/*

# "Build and install": system package provides assimp; copy into /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r /usr/include/assimp /fuzz/install/include/ && \
    ( [ -f /usr/lib/x86_64-linux-gnu/libassimp.a ] && cp /usr/lib/x86_64-linux-gnu/libassimp.a /fuzz/install/lib/ || true ) && \
    cp -P /usr/lib/x86_64-linux-gnu/libassimp.so* /fuzz/install/lib/

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:$PKG_CONFIG_PATH
ENV LD_LIBRARY_PATH=/fuzz/install/lib:$LD_LIBRARY_PATH
