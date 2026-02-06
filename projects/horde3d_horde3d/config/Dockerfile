ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for OpenGL and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libx11-dev \
    libglvnd-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Horde3D
WORKDIR /fuzz/src

# Create build directory
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DHORDE3D_BUILD_EXAMPLES=OFF \
    -DHORDE3D_BUILD_EDITOR=OFF

RUN cmake --build build --target install -j$(nproc)

# Install public headers (project does not install them on Linux)
RUN mkdir -p /fuzz/install/include && \
    cp Horde3D/Bindings/C++/Horde3D.h /fuzz/install/include/ && \
    cp Horde3D/Bindings/C++/Horde3DUtils.h /fuzz/install/include/
