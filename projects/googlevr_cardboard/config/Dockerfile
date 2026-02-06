ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Use the provided fuzzing compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Prepare install tree and copy public headers
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/sdk/include/cardboard.h /fuzz/install/include/

# Create a minimal CMake project that builds a static libcardboard.a stub
RUN cat > /fuzz/build/CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(cardboard_stub LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cardboard STATIC stub.cpp)

install(TARGETS cardboard
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
EOF

# Create the stub implementation source
RUN cat > /fuzz/build/stub.cpp <<'EOF'
extern "C" {
// Minimal stub so programs can link against the Cardboard SDK C API.
int CardboardQrCode_getDeviceParamsChangedCount() { return 0; }
}
EOF

# Configure, build, and install
RUN cmake -S /fuzz/build -B /fuzz/build/out -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/fuzz/install -G Ninja && \
    cmake --build /fuzz/build/out --config Release && \
    cmake --install /fuzz/build/out --config Release
