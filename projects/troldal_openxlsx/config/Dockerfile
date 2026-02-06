ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (ensure cmake and ninja are present)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to LibAFL wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src/OpenXLSX

# Configure
RUN cmake -G Ninja -S . -B build \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DOPENXLSX_LIBRARY_TYPE=STATIC \
    -DOPENXLSX_ENABLE_LTO=OFF

# Build and install
RUN cmake --build build --target OpenXLSX --config Release && \
    cmake --install build --config Release && \
    mkdir -p /fuzz/install/include/OpenXLSX/external && \
    cp -R /fuzz/src/OpenXLSX/external/* /fuzz/install/include/OpenXLSX/external/
