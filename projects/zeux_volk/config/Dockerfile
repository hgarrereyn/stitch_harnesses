ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and Vulkan development headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libvulkan-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install volk as a static library
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DVOLK_INSTALL=ON \
    -DVULKAN_HEADERS_INSTALL_DIR=/usr \
    /fuzz/src \
 && cmake --build . --target install --config Release
