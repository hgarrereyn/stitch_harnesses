ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra dependencies required; we will package a header-only utility and a minimal static library
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/tensorrtx && \
    cd /fuzz/build && \
    printf "// dummy translation unit for static lib\nint __tensorrtx_utils_dummy = 0;\n" > utils_dummy.cpp && \
    stitch_libafl_cxx -O2 -c utils_dummy.cpp -o utils_dummy.o && \
    ar rcs libtensorrtx_utils.a utils_dummy.o && \
    mv libtensorrtx_utils.a /fuzz/install/lib/ && \
    cp /fuzz/src/yolov5/src/utils.h /fuzz/install/include/tensorrtx/
