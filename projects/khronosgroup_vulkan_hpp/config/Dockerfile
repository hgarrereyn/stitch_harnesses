ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tooling
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config && rm -rf /var/lib/apt/lists/*

# Configure and install to /fuzz/install using the provided clang wrappers
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DVulkanHeaders_INCLUDE_DIR=/fuzz/src \
    -DVULKAN_HPP_INSTALL=ON \
    -DVULKAN_HPP_GENERATOR_BUILD=OFF \
    -DVULKAN_HPP_SAMPLES_BUILD=OFF \
    -DVULKAN_HPP_TESTS_BUILD=OFF

RUN cmake --build /fuzz/build --target install --parallel

# Also install the C Vulkan headers (and related include directories) that Vulkan-Hpp includes
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/Vulkan-Headers/include/* /fuzz/install/include/
