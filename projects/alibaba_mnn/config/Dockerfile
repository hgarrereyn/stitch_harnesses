ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build MNN as a static library and install to /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DMNN_BUILD_SHARED_LIBS=OFF \
    -DMNN_BUILD_TOOLS=OFF \
    -DMNN_BUILD_CONVERTER=OFF \
    -DMNN_BUILD_TEST=OFF \
    -DMNN_BUILD_BENCHMARK=OFF \
    -DMNN_OPENMP=OFF \
    -DMNN_METAL=OFF -DMNN_OPENCL=OFF -DMNN_OPENGL=OFF -DMNN_VULKAN=OFF -DMNN_CUDA=OFF -DMNN_TENSORRT=OFF -DMNN_COREML=OFF -DMNN_NNAPI=OFF -DMNN_QNN=OFF -DMNN_ONEDNN=OFF -DMNN_BUILD_LLM=OFF -DMNN_BUILD_DIFFUSION=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)
