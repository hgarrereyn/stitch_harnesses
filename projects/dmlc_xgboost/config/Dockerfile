ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make build-essential ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure and build XGBoost as a static library without OpenMP/GPU/bindings
RUN cmake -S /fuzz/src -B /tmp/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_STATIC_LIB=ON \
    -DUSE_OPENMP=OFF \
    -DUSE_CUDA=OFF \
    -DJVM_BINDINGS=OFF \
    -DR_LIB=OFF \
    -DADD_PKGCONFIG=OFF \
 && cmake --build /tmp/build -j \
 && cmake --install /tmp/build \
 && rm -rf /tmp/build
