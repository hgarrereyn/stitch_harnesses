ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    python3 \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz

# Configure
RUN mkdir -p build && cd build && \
  cmake -G Ninja /fuzz/src/llvm \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_BUILD_TOOLS=OFF \
    -DLLVM_ENABLE_PROJECTS="" \
    -DLLVM_TARGETS_TO_BUILD=Native \
    -DLLVM_ENABLE_ZLIB=OFF \
    -DLLVM_ENABLE_ZSTD=OFF \
    -DLLVM_ENABLE_TERMINFO=OFF \
    -DLLVM_ENABLE_LIBXML2=OFF \
    -DLLVM_ENABLE_ASSERTIONS=OFF

# Build only LLVMDemangle static lib and stage headers/libs manually
RUN cmake --build /fuzz/build --target LLVMDemangle -j$(nproc) && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/llvm && \
    cp /fuzz/build/lib/libLLVMDemangle.a /fuzz/install/lib/ && \
    cp -r /fuzz/src/llvm/include/* /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/llvm/Config && \
    cp -r /fuzz/build/include/llvm/Config/* /fuzz/install/include/llvm/Config/
