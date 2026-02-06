ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build nndeploy as a static library with minimal features
WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_NNDEPLOY_BUILD_SHARED=OFF \
    -DENABLE_NNDEPLOY_PLUGIN=OFF \
    -DENABLE_NNDEPLOY_DEMO=OFF \
    -DENABLE_NNDEPLOY_PYTHON=OFF \
    -DENABLE_NNDEPLOY_TEST=OFF \
    -DENABLE_NNDEPLOY_OPENCV=OFF \
 && cmake --build build --target install \
 && set -ex \
 && INST_DIR=$(echo /fuzz/src/build/nndeploy_*_Linux_*_Release_*) \
 && mkdir -p /fuzz/install \
 && cp -r "$INST_DIR"/* /fuzz/install/
