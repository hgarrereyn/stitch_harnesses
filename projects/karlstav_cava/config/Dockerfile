ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for cavacore (FFTW3) and build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    libfftw3-dev \
    cmake \
    ninja-build \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build cavacore static library using CMake and install headers/libs into /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Configure and build
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build build --target cavacore --config Release

# Manually install since upstream CMakeLists has no install() rules
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp build/libcavacore.a /fuzz/install/lib/ \
 && cp cavacore.h /fuzz/install/include/
