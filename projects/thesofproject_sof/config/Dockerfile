ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install SOF as a library
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCONFIG_LIBRARY=ON \
    -DCONFIG_LIBRARY_STATIC=ON \
    -DBUILD_UNIT_TESTS=OFF \
    -DINIT_CONFIG=src/arch/host/configs/library_defconfig \
 && cmake --build /fuzz/build --target install
