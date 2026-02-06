ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    git \
    ca-certificates \
    pkg-config \
    cmake \
    ninja-build \
    make \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install IGL
WORKDIR /fuzz/src

# Configure: disable samples/tests/extras, enable install, build static, use EGL/GLES on Linux
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DIGL_WITH_SAMPLES=OFF \
    -DIGL_WITH_IGLU=ON \
    -DIGL_WITH_SHELL=OFF \
    -DIGL_WITH_TESTS=OFF \
    -DIGL_WITH_VULKAN=OFF \
    -DIGL_WITH_METAL=OFF \
    -DIGL_ENABLE_INSTALL=ON

RUN cmake --build build -j
RUN cmake --install build
