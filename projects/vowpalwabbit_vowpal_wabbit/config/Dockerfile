ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install VW
WORKDIR /fuzz/src

# Configure with static libraries and installation enabled
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DVW_INSTALL=ON \
    -DVW_FEAT_LDA=OFF \
    -DUSE_LATEST_STD=ON \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --target install --config Release
