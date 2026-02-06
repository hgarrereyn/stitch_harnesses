ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Vulkan worker
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libvulkan-dev \
    libglfw3-dev \
    libgflags-dev \
    ca-certificates \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build a static library from the Vulkan worker sources and install headers
ENV SRC_DIR=/fuzz/src \
    INSTALL_PREFIX=/fuzz/install

RUN mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include/graphicsfuzz-vkworker /tmp/build && \
    cd /tmp/build && \
    stitch_libafl_cxx -O2 -fPIC \
      -I"${SRC_DIR}/vulkan-worker/src/common" \
      -I"${SRC_DIR}/vulkan-worker/src/linux" \
      -I"${SRC_DIR}/third_party/cJSON" \
      -I"${SRC_DIR}/third_party/lodepng" \
      -c "${SRC_DIR}/vulkan-worker/src/common/vulkan_worker.cc" -o vulkan_worker.o && \
    stitch_libafl_cxx -O2 -fPIC -DVK_RESULT_RANGE_SIZE=100000 \
      -I"${SRC_DIR}/vulkan-worker/src/common" \
      -I"${SRC_DIR}/vulkan-worker/src/linux" \
      -c "${SRC_DIR}/vulkan-worker/src/common/vkcheck.cc" -o vkcheck.o && \
    stitch_libafl_cxx -O2 -fPIC \
      -I"${SRC_DIR}/vulkan-worker/src/linux" \
      -I"${SRC_DIR}/vulkan-worker/src/common" \
      -c "${SRC_DIR}/vulkan-worker/src/linux/platform.cc" -o platform_linux.o && \
    stitch_libafl_cc -O2 -fPIC -I"${SRC_DIR}/third_party/cJSON" -c "${SRC_DIR}/third_party/cJSON/cJSON.c" -o cJSON.o && \
    stitch_libafl_cxx -O2 -fPIC -I"${SRC_DIR}/third_party/lodepng" -c "${SRC_DIR}/third_party/lodepng/lodepng.cpp" -o lodepng.o && \
    ar rcs ${INSTALL_PREFIX}/lib/libvkworker.a vulkan_worker.o vkcheck.o platform_linux.o cJSON.o lodepng.o && \
    cp "${SRC_DIR}/vulkan-worker/src/common/vulkan_worker.h" ${INSTALL_PREFIX}/include/graphicsfuzz-vkworker/ && \
    cp "${SRC_DIR}/vulkan-worker/src/common/vkcheck.h" ${INSTALL_PREFIX}/include/graphicsfuzz-vkworker/ && \
    cp "${SRC_DIR}/vulkan-worker/src/linux/platform.h" ${INSTALL_PREFIX}/include/graphicsfuzz-vkworker/
