ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: build tools, protoc and python3 for generator packaging during CMake install
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    protobuf-compiler \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install nanopb (static library preferred)
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -Dnanopb_BUILD_RUNTIME=ON \
    -Dnanopb_BUILD_GENERATOR=ON \
 && cmake --build build --target install -- -v
