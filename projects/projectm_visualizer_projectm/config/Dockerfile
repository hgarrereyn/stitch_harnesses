ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build/runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    ninja-build \
    cmake \
    libgl1-mesa-dev \
    libglvnd-dev \
    libx11-dev \
    libxext-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install static lib
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_INSTALL=ON \
    -DENABLE_SDL_UI=OFF \
    -DENABLE_SYSTEM_GLM=OFF \
    -DENABLE_SYSTEM_PROJECTM_EVAL=OFF \
 && cmake --build build -j $(nproc) \
 && cmake --install build
