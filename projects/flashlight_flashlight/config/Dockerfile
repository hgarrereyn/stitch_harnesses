ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    libcereal-dev \
    && rm -rf /var/lib/apt/lists/*

# Workaround broken cereal CMake target that references /include
RUN ln -s /usr/include /include || true

# Configure, build, install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src
RUN mkdir -p build && cd build \
 && cmake .. \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_CXX_FLAGS=-Dcontains=count \
    -DFL_BUILD_STANDALONE=OFF \
    -DFL_BUILD_EXAMPLES=OFF \
    -DFL_BUILD_TESTS=OFF \
    -DFL_BUILD_CONTRIB=OFF \
    -DFL_BUILD_DISTRIBUTED=OFF \
    -DFL_USE_ARRAYFIRE=OFF \
    -DFL_USE_ONEDNN=OFF \
    -DFL_USE_JIT=OFF \
    -DFL_USE_TENSOR_STUB=ON \
 && ninja -j"$(nproc)" \
 && ninja install
