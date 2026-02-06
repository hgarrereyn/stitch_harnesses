ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install static liblz4 to /fuzz/install using gf_libafl toolchain
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Build only the static library and manually install headers and library
RUN make -C lib clean && \
    make -C lib -j"$(nproc)" liblz4.a BUILD_SHARED=no BUILD_STATIC=yes && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp lib/liblz4.a /fuzz/install/lib/ && \
    cp lib/lz4.h lib/lz4hc.h lib/lz4frame.h lib/lz4frame_static.h lib/lz4file.h /fuzz/install/include/
