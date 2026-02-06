ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      cmake ninja-build build-essential && \
    rm -rf /var/lib/apt/lists/*

# Build and install JoltPhysics as a static library
WORKDIR /fuzz/build

# Configure
RUN cmake -G Ninja \
    -S /fuzz/src/Build \
    -B . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_INSTALL=ON \
    -DTARGET_UNIT_TESTS=OFF \
    -DTARGET_HELLO_WORLD=OFF \
    -DTARGET_PERFORMANCE_TEST=OFF \
    -DTARGET_SAMPLES=OFF \
    -DTARGET_VIEWER=OFF \
    -DJPH_USE_VK=OFF \
    -DJPH_USE_DX12=OFF \
    -DJPH_USE_MTL=OFF

# Build and install
RUN cmake --build . --target install --config Release
