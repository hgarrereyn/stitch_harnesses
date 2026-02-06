ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for raylib and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-pip pkg-config ca-certificates \
    ninja-build make \
    libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev \
    libxxf86vm-dev libasound2-dev libgl1-mesa-dev \
 && rm -rf /var/lib/apt/lists/* \
 && python3 -m pip install --no-cache-dir --upgrade pip \
 && python3 -m pip install --no-cache-dir cmake

# Build and install raylib as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -D CMAKE_C_COMPILER=stitch_libafl_cc \
    -D CMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -D CMAKE_INSTALL_PREFIX=/fuzz/install \
    -D BUILD_SHARED_LIBS=OFF \
    -D USE_EXTERNAL_GLFW=IF_POSSIBLE \
    -D CMAKE_BUILD_TYPE=Release \
 && cmake --build build --target install
