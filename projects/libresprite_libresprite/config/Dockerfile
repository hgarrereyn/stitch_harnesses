ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Manually build the minimal static clip library without CMake (to avoid high CMake version requirement)
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    cd /fuzz/src/src/clip; \
    stitch_libafl_cxx -std=c++17 -O2 -c clip.cpp -o /fuzz/build/clip.o; \
    stitch_libafl_cxx -std=c++17 -O2 -c image.cpp -o /fuzz/build/image.o; \
    stitch_libafl_cxx -std=c++17 -O2 -c clip_none.cpp -o /fuzz/build/clip_none.o; \
    ar rcs /fuzz/install/lib/libclip.a /fuzz/build/clip.o /fuzz/build/image.o /fuzz/build/clip_none.o; \
    cp /fuzz/src/src/clip/clip.h /fuzz/src/src/clip/clip_common.h /fuzz/install/include/
