ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static library for nav2_voxel_grid with stubbed rclcpp logging

RUN set -eux; \
    apt-get update; apt-get install -y --no-install-recommends ca-certificates build-essential; \
    rm -rf /var/lib/apt/lists/*

# Prepare install dirs
RUN mkdir -p /fuzz/build /fuzz/install/include/nav2_voxel_grid /fuzz/install/include/rclcpp /fuzz/install/lib

# Install the public header
RUN cp /fuzz/src/nav2_voxel_grid/include/nav2_voxel_grid/voxel_grid.hpp /fuzz/install/include/nav2_voxel_grid/

# Provide minimal stub rclcpp headers so voxel_grid can compile without full ROS 2
RUN cat > /fuzz/install/include/rclcpp/logger.hpp <<'EOF'
#pragma once
#include <string>
namespace rclcpp {
  class Logger {
  public: Logger() = default;
  };
  inline Logger get_logger(const std::string &){ return Logger(); }
} // namespace rclcpp
EOF
RUN cat > /fuzz/install/include/rclcpp/logging.hpp <<'EOF'
#pragma once
#include "rclcpp/logger.hpp"
#ifndef RCLCPP_DEBUG
#define RCLCPP_DEBUG(logger, ...) do { (void)sizeof(logger); } while(0)
#endif
#ifndef RCLCPP_INFO
#define RCLCPP_INFO(logger, ...) do { (void)sizeof(logger); } while(0)
#endif
EOF

# Build static library from the source file
RUN set -eux; \
    cd /fuzz/build; \
    stitch_libafl_cxx -I/fuzz/install/include -I/fuzz/src/nav2_voxel_grid/include -include assert.h -fPIC -c /fuzz/src/nav2_voxel_grid/src/voxel_grid.cpp -o voxel_grid.o; \
    ar rcs /fuzz/install/lib/libnav2_voxel_grid.a voxel_grid.o; \
    ranlib /fuzz/install/lib/libnav2_voxel_grid.a

ENV CPATH=/fuzz/install/include
ENV LIBRARY_PATH=/fuzz/install/lib
