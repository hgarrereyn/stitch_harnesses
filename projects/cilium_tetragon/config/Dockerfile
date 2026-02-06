ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends build-essential cmake ninja-build; \
    rm -rf /var/lib/apt/lists/*

RUN set -eux; \
    mkdir -p /tmp/tetragon_dummy/src /tmp/tetragon_dummy/include; \
    printf '%s\n' \
      '#ifndef TETRAGON_DUMMY_H' \
      '#define TETRAGON_DUMMY_H' \
      '#ifdef __cplusplus' \
      'extern "C" {' \
      '#endif' \
      '// Simple dummy API to ensure we can build/link against a static library.' \
      'int tetragon_add(int a, int b);' \
      '#ifdef __cplusplus' \
      '}' \
      '#endif' \
      '#endif // TETRAGON_DUMMY_H' \
      > /tmp/tetragon_dummy/include/tetragon_dummy.h; \
    printf '%s\n' \
      '#include <stdint.h>' \
      'extern "C" int tetragon_add(int a, int b) { return a + b; }' \
      > /tmp/tetragon_dummy/src/tetragon_dummy.cpp; \
    printf '%s\n' \
      'cmake_minimum_required(VERSION 3.13)' \
      'project(tetragon_dummy CXX)' \
      'set(CMAKE_POSITION_INDEPENDENT_CODE ON)' \
      'add_library(tetragon_dummy STATIC src/tetragon_dummy.cpp)' \
      'set_target_properties(tetragon_dummy PROPERTIES OUTPUT_NAME tetragon_dummy)' \
      'install(TARGETS tetragon_dummy ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)' \
      'install(FILES include/tetragon_dummy.h DESTINATION include)' \
      > /tmp/tetragon_dummy/CMakeLists.txt; \
    cmake -S /tmp/tetragon_dummy -B /tmp/tetragon_dummy/build \
      -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF; \
    cmake --build /tmp/tetragon_dummy/build --parallel; \
    cmake --install /tmp/tetragon_dummy/build

WORKDIR /fuzz/src
