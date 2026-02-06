ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Create a minimal CMake project that reuses the repo's md.cmake only
RUN mkdir -p /fuzz/minimd
RUN /bin/sh -c 'printf "cmake_minimum_required(VERSION 3.16)\nproject(minimd C)\nset(CMAKE_C_STANDARD 11)\ninclude(/fuzz/src/app/src/main/cpp/recipes/md.cmake)\n" > /fuzz/minimd/CMakeLists.txt'

# Configure and build the md static library
RUN cmake -S /fuzz/minimd -B /fuzz/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build --target md -j$(nproc)

# Install archive and header
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp /fuzz/build/libmd.a /fuzz/install/lib/ \
 && cp /fuzz/build/sha1.h /fuzz/install/include/
