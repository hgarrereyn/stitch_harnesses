ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libspdlog-dev \
 && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
RUN mkdir -p /fuzz/install/include/crossdesk /fuzz/install/lib

# Generate a minimal CMake project to build a small static library from available sources
# We avoid building the full application (which requires submodules and many deps)
RUN cat > /tmp/CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(crossdesk_mini LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

# Dependencies
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Library sources from the repository
add_library(crossdesk_mini STATIC
  /fuzz/src/src/log/rd_log.cpp
  /fuzz/src/src/common/platform.cpp
  /fuzz/src/src/path_manager/path_manager.cpp
)

target_include_directories(crossdesk_mini
  PUBLIC
    /fuzz/src/src/log
    /fuzz/src/src/common
    /fuzz/src/src/path_manager
)

target_link_libraries(crossdesk_mini PRIVATE spdlog::spdlog fmt::fmt)

# Install targets and headers
install(TARGETS crossdesk_mini ARCHIVE DESTINATION lib)
install(FILES
  /fuzz/src/src/log/rd_log.h
  /fuzz/src/src/common/platform.h
  /fuzz/src/src/common/display_info.h
  /fuzz/src/src/path_manager/path_manager.h
  DESTINATION include/crossdesk)
EOF

# Configure, build and install
RUN cmake -S /tmp -B /tmp/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /tmp/build --target install --config Release
