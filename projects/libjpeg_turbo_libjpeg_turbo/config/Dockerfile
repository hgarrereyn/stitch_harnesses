ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install libjpeg-turbo statically into /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends ninja-build cmake && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_SHARED=0 \
    -DENABLE_STATIC=1 \
    -DWITH_TURBOJPEG=1 \
    -DWITH_JAVA=0 \
    -DWITH_TOOLS=0 \
    -DWITH_TESTS=0 \
    -DWITH_SIMD=0 && \
    cmake --build /fuzz/build --target install
