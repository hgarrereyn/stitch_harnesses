ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make git ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build SPIRV-Cross as static libraries, install to /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSPIRV_CROSS_STATIC=ON \
    -DSPIRV_CROSS_SHARED=OFF \
    -DSPIRV_CROSS_CLI=OFF \
    -DSPIRV_CROSS_ENABLE_TESTS=OFF \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx && \
    cmake --build /fuzz/build --target install -j$(nproc)
