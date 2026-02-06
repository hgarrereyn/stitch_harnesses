ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (make for Makefile, binutils for ar)
RUN apt-get update && apt-get install -y --no-install-recommends make binutils && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build only the static library and install headers/libs to /fuzz/install
RUN make CC=stitch_libafl_cc CFLAGS="-O2 -g -fPIC" libs \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp build/libmpc.a /fuzz/install/lib/ \
 && cp mpc.h /fuzz/install/include/
