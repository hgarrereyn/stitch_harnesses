ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libeigen3-dev \
    libboost-serialization-dev \
    libboost-filesystem-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Pinocchio (minimal features)
WORKDIR /fuzz/src

RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DBUILD_PYTHON_INTERFACE=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_TESTING=OFF \
      -DBUILD_UTILS=OFF \
      -DBUILD_WITH_URDF_SUPPORT=OFF \
      -DBUILD_WITH_SDF_SUPPORT=OFF \
      -DBUILD_WITH_COLLISION_SUPPORT=OFF \
      -DENABLE_TEMPLATE_INSTANTIATION=ON \
      .. && \
    ninja -j$(nproc) && \
    ninja install
