ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed to configure/build with CMake/Ninja
RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static libopus with CMake
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DOPUS_BUILD_TESTING=OFF \
    -DOPUS_BUILD_PROGRAMS=OFF \
 && cmake --build build -j \
 && cmake --install build
