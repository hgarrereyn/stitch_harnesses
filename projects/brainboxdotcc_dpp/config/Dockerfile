ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build dependencies and tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build the project
WORKDIR /fuzz

# Configure with cmake (build shared to ensure installation works), disable voice to avoid extra deps
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_VOICE_SUPPORT=OFF \
    -DDPP_INSTALL=ON \
    -DDPP_BUILD_TEST=OFF \
    -DDPP_NO_VCPKG=ON \
    -DDPP_NO_CONAN=ON

RUN cmake --build /fuzz/build --parallel
RUN cmake --install /fuzz/build
