ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static core library only
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DAC_SHARED_LIB=OFF \
    -DAC_BUILD_CLI=OFF \
    -DAC_BUILD_GUI=OFF \
    -DAC_BUILD_VIDEO=OFF \
    -DAC_BUILD_FILTER_AVISYNTH=OFF \
    -DAC_BUILD_FILTER_VAPOURSYNTH=OFF \
    -DAC_BUILD_FILTER_DIRECTSHOW=OFF \
    -DAC_BUILD_FILTER_AVISYNTH_VAPOURSYNTH=OFF \
    -DAC_BUILD_BINDING_C=OFF \
    -DAC_BUILD_BINDING_PYTHON=OFF \
    -DAC_TOOLS_BENCHMARK=OFF \
    -DAC_TEST_UTIL=OFF \
    -DAC_TEST_VIDEO=OFF \
    -DAC_CORE_WITH_OPENCL=OFF \
    -DAC_CORE_WITH_CUDA=OFF \
    -DAC_CORE_WITH_EIGEN3=OFF
RUN cmake --build build --target install -j$(nproc)
