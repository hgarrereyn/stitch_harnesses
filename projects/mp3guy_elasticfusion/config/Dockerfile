ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build to provide a usable static library from the Utils subset
# of ElasticFusion that has no external dependencies (Intrinsics/Resolution).
# The full project requires CUDA/OpenGL, which are not needed for API compilation tests.

RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build && \
    cp /fuzz/src/Core/Utils/Intrinsics.h /fuzz/install/include/ && \
    cp /fuzz/src/Core/Utils/Resolution.h /fuzz/install/include/ && \
    "$CXX" -std=c++17 -O2 -I/fuzz/src/Core/Utils -c /fuzz/src/Core/Utils/Intrinsics.cpp -o /tmp/build/Intrinsics.o && \
    "$CXX" -std=c++17 -O2 -I/fuzz/src/Core/Utils -c /fuzz/src/Core/Utils/Resolution.cpp -o /tmp/build/Resolution.o && \
    ar rcs /fuzz/install/lib/libefusion.a /tmp/build/Intrinsics.o /tmp/build/Resolution.o
