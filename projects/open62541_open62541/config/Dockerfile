ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and Python for code generation
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install open62541 (build shared to avoid archive format issues)
WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=ON \
    -DUA_ENABLE_ENCRYPTION=OFF \
    -DUA_BUILD_EXAMPLES=OFF \
    -DUA_BUILD_UNIT_TESTS=OFF \
    -DUA_BUILD_TOOLS=OFF
RUN cmake --build build --target install --config Release
