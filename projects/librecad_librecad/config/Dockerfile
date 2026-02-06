ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake, ninja, ar/ranlib, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Prepare a minimal CMake project to build libdxfrw as a static library
RUN mkdir -p /tmp/build_libdxfrw && \
    cat > /tmp/build_libdxfrw/CMakeLists.txt <<'CMK'
cmake_minimum_required(VERSION 3.16)
project(dxfrw LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Sources
file(GLOB DXFRW_SRC
  "/fuzz/src/libraries/libdxfrw/src/*.cpp"
  "/fuzz/src/libraries/libdxfrw/src/intern/*.cpp"
)
add_library(dxfrw STATIC ${DXFRW_SRC})

target_include_directories(dxfrw PUBLIC
  "/fuzz/src/libraries/libdxfrw/src"
  "/fuzz/src/libraries/libdxfrw/src/intern"
)

install(TARGETS dxfrw ARCHIVE DESTINATION lib)
# Install public headers
file(GLOB PUB_HEADERS
  "/fuzz/src/libraries/libdxfrw/src/*.h"
)
install(FILES ${PUB_HEADERS} DESTINATION include/libdxfrw)
CMK

# Configure, build, and install
RUN cmake -S /tmp/build_libdxfrw -B /tmp/build_libdxfrw/build \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /tmp/build_libdxfrw/build && \
    cmake --install /tmp/build_libdxfrw/build && \
    rm -rf /tmp/build_libdxfrw
