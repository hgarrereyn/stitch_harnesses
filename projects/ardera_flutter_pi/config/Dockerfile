ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies required to build flutter-pi
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config build-essential cmake \
    libdrm-dev libgbm-dev libegl1-mesa-dev libgles2-mesa-dev \
    libsystemd-dev libinput-dev libudev-dev libxkbcommon-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Use the fuzzer-provided compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build, and install
RUN cmake -S /fuzz/src -B /fuzz/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DENABLE_OPENGL=ON -DTRY_ENABLE_OPENGL=ON \
      -DENABLE_VULKAN=OFF -DTRY_ENABLE_VULKAN=OFF \
      -DENABLE_TESTS=OFF && \
    cmake --build /fuzz/build -j && \
    cmake --install /fuzz/build && \
    mkdir -p /fuzz/install/include && \
    cp /fuzz/build/config.h /fuzz/install/include/
