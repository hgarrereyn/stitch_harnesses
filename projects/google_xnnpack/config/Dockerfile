ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    python3 \
    ca-certificates \
    curl \
    unzip \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install XNNPACK
WORKDIR /fuzz

# Configure with CMake to build static library and download third-party deps
RUN mkdir -p build && cd build && \
    cmake -G Ninja /fuzz/src \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DXNNPACK_BUILD_TESTS=OFF \
      -DXNNPACK_BUILD_BENCHMARKS=OFF \
      -DXNNPACK_BUILD_LIBRARY=ON \
      -DXNNPACK_LIBRARY_TYPE=static \
      -DXNNPACK_USE_SYSTEM_LIBS=OFF && \
    ninja install

# Copy third-party headers and libs needed by public headers
# Ensure pthreadpool/cpuinfo headers are available to consumers, and libs are available for linking
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    # Install experimental.h which isn't installed by default
    cp -a /fuzz/src/include/experimental.h /fuzz/install/include/ || true; \
    if [ -d /fuzz/build/pthreadpool-source/include ]; then \
      cp -r /fuzz/build/pthreadpool-source/include/* /fuzz/install/include/; \
    fi; \
    if [ -d /fuzz/build/cpuinfo-source/include ]; then \
      cp -r /fuzz/build/cpuinfo-source/include/* /fuzz/install/include/; \
    fi; \
    if [ -d /fuzz/build/FXdiv-source ]; then \
      cp -r /fuzz/build/FXdiv-source/include/* /fuzz/install/include/ || true; \
    fi; \
    # Copy built static libs if present
    cp -a /fuzz/build/pthreadpool/*.a /fuzz/install/lib/ || true; \
    cp -a /fuzz/build/cpuinfo/*.a /fuzz/install/lib/ || true; \
    cp -a /fuzz/build/FXdiv/*.a /fuzz/install/lib/ || true
