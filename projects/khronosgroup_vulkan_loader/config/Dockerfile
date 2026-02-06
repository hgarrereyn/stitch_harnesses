ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and Vulkan headers
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        git \
        cmake \
        ninja-build \
        pkg-config \
        python3 \
        libvulkan-dev \
    && rm -rf /var/lib/apt/lists/*

# Checkout a Vulkan-Loader version that matches system Vulkan headers
RUN git -C /fuzz/src checkout v1.3.204 || git -C /fuzz/src checkout tags/v1.3.204 || true

# Provide a minimal VulkanHeaders CMake package so find_package(VulkanHeaders CONFIG) works
RUN mkdir -p /opt/vkh/lib/cmake/VulkanHeaders && \
    printf "set(VulkanHeaders_VERSION \"1.3.204\")\nif(NOT TARGET Vulkan::Headers)\n  add_library(Vulkan::Headers INTERFACE IMPORTED)\n  set_target_properties(Vulkan::Headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES \"/usr/include\")\nendif()\n" > /opt/vkh/lib/cmake/VulkanHeaders/VulkanHeadersConfig.cmake && \
    printf "set(PACKAGE_VERSION \"1.3.204\")\n# Always report compatible; exact match if equal\nif(DEFINED PACKAGE_FIND_VERSION)\n  if(PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)\n    set(PACKAGE_VERSION_EXACT TRUE)\n  else()\n    set(PACKAGE_VERSION_EXACT FALSE)\n  endif()\n  set(PACKAGE_VERSION_COMPATIBLE TRUE)\nendif()\n" > /opt/vkh/lib/cmake/VulkanHeaders/VulkanHeadersConfigVersion.cmake

# Configure and build Vulkan-Loader
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_PREFIX_PATH=/opt/vkh \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTS=OFF \
    -DBUILD_WSI_XCB_SUPPORT=OFF \
    -DBUILD_WSI_XLIB_SUPPORT=OFF \
    -DBUILD_WSI_XLIB_XRANDR_SUPPORT=OFF \
    -DBUILD_WSI_WAYLAND_SUPPORT=OFF \
    -DBUILD_WSI_DIRECTFB_SUPPORT=OFF
RUN cmake --build /fuzz/build --target install -j$(nproc)

# Ensure headers are available under the install prefix for consumers
RUN mkdir -p /fuzz/install/include && \
    if [ -d /usr/include/vulkan ]; then cp -a /usr/include/vulkan /fuzz/install/include/; fi
