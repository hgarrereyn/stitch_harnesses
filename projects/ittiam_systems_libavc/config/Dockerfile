ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz

# Configure with cmake using the provided compilers and install prefix
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build only the static libraries (skip examples/fuzzers to speed up)
RUN cmake --build /fuzz/build --target libavcdec libavcenc -j$(nproc)

# Install: manually copy static libs and public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp /fuzz/build/libavcdec.a /fuzz/install/lib/ \
    && cp /fuzz/build/libavcenc.a /fuzz/install/lib/ \
    && cp /fuzz/src/common/ih264_typedefs.h /fuzz/install/include/ \
    && cp /fuzz/src/decoder/iv.h /fuzz/install/include/ \
    && cp /fuzz/src/decoder/ivd.h /fuzz/install/include/ \
    && cp /fuzz/src/decoder/ih264d.h /fuzz/install/include/
