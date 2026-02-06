ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /tmp/build && cd /tmp/build && \
    cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(emscripten_core_emscripten_stb C)

add_library(emscripten_core_stb STATIC
  /fuzz/src/system/lib/stb_image.c
)
# Include emscripten headers and third_party for stb_image.h
# (we install both below so consumers can include them from /fuzz/install/include)
target_include_directories(emscripten_core_stb PUBLIC
  $<BUILD_INTERFACE:/fuzz/src/system/include>
  $<BUILD_INTERFACE:/fuzz/src/third_party>
)

# Installation
include(GNUInstallDirs)
install(TARGETS emscripten_core_stb
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
# Install the public headers: stb_image.h and the emscripten headers tree.
install(FILES /fuzz/src/third_party/stb_image.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY /fuzz/src/system/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
EOF

RUN cd /tmp/build && cmake -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      . && \
    ninja -v && ninja install && \
    rm -rf /tmp/build
