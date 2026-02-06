ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config build-essential \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /build /fuzz/install \
 && cmake -S /fuzz/src -B /build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DGGML_OPENMP=OFF \
    -DGGML_BLAS=OFF \
    -DGGML_CUDA=OFF \
    -DGGML_HIP=OFF \
    -DGGML_VULKAN=OFF \
    -DGGML_WEBGPU=OFF \
    -DGGML_SYCL=OFF \
    -DGGML_METAL=OFF \
    -DGGML_RPC=OFF \
    -DGGML_ZDNN=OFF \
    -DGGML_ZENDNN=OFF \
    -DGGML_OPENCL=OFF \
    -DGGML_NATIVE=OFF \
 && cmake --build /build --config Release -j \
 && cmake --install /build --config Release
