ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependency for Eigen (used by public headers)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libeigen3-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/lidar_camera_calibration /fuzz/install/include/ros \
    && cp -r /fuzz/src/include/lidar_camera_calibration/*.h /fuzz/install/include/lidar_camera_calibration/

# Create minimal ROS stub header so headers compile without ROS
RUN printf '%s\n' \
  '#pragma once' \
  '#include <string>' \
  '#include <iostream>' \
  '#include <iomanip>' \
  'namespace ros {' \
  'namespace package {' \
  'inline std::string getPath(const std::string&) { return std::string("/fuzz/src"); }' \
  '}' \
  'inline void shutdown() {}' \
  '}' \
  '#ifndef ROS_ASSERT' \
  '#define ROS_ASSERT(x) do { if(!(x)) { std::cerr << "ROS_ASSERT failed: " << #x << "\\n"; } } while(0)' \
  '#endif' \
  '#ifndef ROS_INFO_STREAM' \
  '#define ROS_INFO_STREAM(x) do { std::cout << x << std::endl; } while(0)' \
  '#endif' \
  > /fuzz/install/include/ros_stubs.h

# Build an empty static library to link against
RUN bash -lc "\
  echo 'extern \"C\" void __lc_dummy(){}' > /fuzz/src/empty.cpp; \
  $CXX -c /fuzz/src/empty.cpp -O2 -fPIC -o /fuzz/src/empty.o; \
  ar rcs /fuzz/install/lib/liblidar_camera_calibration.a /fuzz/src/empty.o \
"

