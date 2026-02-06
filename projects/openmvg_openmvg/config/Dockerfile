ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and Eigen (for headers in public API)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libeigen3-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install OpenMVG
WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S src -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DOpenMVG_BUILD_SHARED=OFF \
    -DOpenMVG_BUILD_TESTS=OFF \
    -DOpenMVG_BUILD_DOC=OFF \
    -DOpenMVG_BUILD_EXAMPLES=OFF \
    -DOpenMVG_BUILD_SOFTWARES=OFF \
    -DOpenMVG_BUILD_GUI_SOFTWARES=OFF \
    -DOpenMVG_BUILD_OPENGL_EXAMPLES=OFF \
    -DOpenMVG_USE_OPENMP=OFF \
    -DOpenMVG_USE_RERUN=OFF \
 && cmake --build build -j \
 && cmake --install build
