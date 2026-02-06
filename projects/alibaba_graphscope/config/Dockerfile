ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal deps: protobuf and glog
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    protobuf-compiler \
    libprotobuf-dev \
    libgoogle-glog-dev \
    cmake \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Build and install a minimal GraphScope C++ utility library (result + protobuf error code)
WORKDIR /work

# Configure a tiny CMake project that compiles flex/utils/result.cc and the interactive.proto
RUN mkdir -p /work/build && cat > /work/CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(graphscope_utils LANGUAGES CXX)

# Enforce compilers and install prefix
if(NOT CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER gf_libafl_cc)
endif()
if(NOT CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER gf_libafl_cxx)
endif()
set(CMAKE_INSTALL_PREFIX /fuzz/install CACHE PATH "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Protobuf REQUIRED)

# glog doesn't always ship a CMake config on Ubuntu, locate the lib directly
find_library(GLOG_LIB glog REQUIRED)

set(SRC_ROOT /fuzz/src)
set(PROTO_FILE ${SRC_ROOT}/proto/error/interactive.proto)

# Generate protobuf sources and place them under flex/utils/error_pb to match includes
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.cc
         ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.h
  COMMAND ${Protobuf_PROTOC_EXECUTABLE} --cpp_out=${CMAKE_CURRENT_BINARY_DIR} -I ${SRC_ROOT}/proto/error ${PROTO_FILE}
  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/interactive.pb.cc ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.cc
  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/interactive.pb.h ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.h
  DEPENDS ${PROTO_FILE}
  VERBATIM)
add_custom_target(gen_proto ALL DEPENDS 
  ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.h)

add_library(graphscope_utils STATIC
  ${SRC_ROOT}/flex/utils/result.cc
  ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.cc)
add_dependencies(graphscope_utils gen_proto)

target_include_directories(graphscope_utils PUBLIC ${SRC_ROOT} ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(graphscope_utils PUBLIC protobuf::libprotobuf ${GLOG_LIB})

install(TARGETS graphscope_utils ARCHIVE DESTINATION lib)
install(FILES ${SRC_ROOT}/flex/utils/result.h DESTINATION include/flex/utils)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/flex/utils/error_pb/interactive.pb.h DESTINATION include/flex/utils/error_pb)
EOF

RUN cmake -S /work -B /work/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /work/build --target install -j$(nproc)
