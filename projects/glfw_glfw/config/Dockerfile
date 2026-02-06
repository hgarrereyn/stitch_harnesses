ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and X11 development dependencies for GLFW (X11 backend only)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install GLFW as a static library
WORKDIR /fuzz/src

# Configure with CMake, install prefix and static lib, disable extras and Wayland
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DGLFW_BUILD_DOCS=OFF \
    -DGLFW_BUILD_TESTS=OFF \
    -DGLFW_BUILD_EXAMPLES=OFF \
    -DGLFW_BUILD_WAYLAND=OFF \
    -DGLFW_BUILD_X11=ON

RUN cmake --build build --target install -j
