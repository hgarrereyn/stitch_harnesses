ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (cmake/ninja in case base image lacks them)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libncursesw5-dev \
    libunistring-dev \
    libdeflate-dev \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Configure, build, and install notcurses (static + shared), minimal deps
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DUSE_MULTIMEDIA=none \
    -DUSE_PANDOC=OFF \
    -DUSE_DOCTEST=OFF \
    -DBUILD_EXECUTABLES=OFF \
    -DUSE_STATIC=ON

RUN cmake --build build --target install --config RelWithDebInfo
