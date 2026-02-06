ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config build-essential \
      libvulkan-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build (static libs only)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLSFGVK_INSTALL_DEVELOP=ON \
    -DLSFGVK_BUILD_VK_LAYER=OFF \
    -DLSFGVK_BUILD_UI=OFF \
    -DLSFGVK_BUILD_CLI=OFF && \
    cmake --build /fuzz/build --target install -j
