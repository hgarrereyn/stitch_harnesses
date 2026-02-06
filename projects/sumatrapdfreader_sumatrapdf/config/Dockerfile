ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install the unarr static library from the SumatraPDF repo
# Source is mounted at /fuzz/src
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx
ENV PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib \
 && make -C /fuzz/src/ext/unarr clean || true \
 && make -C /fuzz/src/ext/unarr build=release CC=${CC} AR=ar RANLIB=ranlib \
 && cp /fuzz/src/ext/unarr/unarr.h ${PREFIX}/include/ \
 && cp /fuzz/src/ext/unarr/build/release/libunarr.a ${PREFIX}/lib/
