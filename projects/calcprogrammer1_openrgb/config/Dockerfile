ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Create a minimal CMake build to build a static lib exposing simple public headers
RUN printf '%s\n' \
  'cmake_minimum_required(VERSION 3.16)' \
  'project(OpenRGBMini LANGUAGES C CXX)' \
  '' \
  'add_library(openrgbmini STATIC' \
  '    NetworkProtocol.cpp' \
  '    StringUtils.cpp' \
  ')' \
  '' \
  'target_include_directories(openrgbmini PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})' \
  '' \
  'install(TARGETS openrgbmini ARCHIVE DESTINATION lib)' \
  'install(FILES' \
  '    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkProtocol.h' \
  '    ${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.h' \
  '    DESTINATION include)' \
  > CMakeLists.txt

# Configure, build and install
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build build --parallel \
 && cmake --install build
