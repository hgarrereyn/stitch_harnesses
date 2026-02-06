ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_GUI=OFF \
    -DBUILD_TESTS=OFF \
    -DUSE_BUNDLED_TINYXML2=ON \
    -DHAVE_RULES=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    /fuzz/src
RUN ninja -j$(nproc)

# Install headers and library manually
RUN mkdir -p /fuzz/install/include/cppcheck /fuzz/install/lib \
 && cp -a /fuzz/src/lib/*.h /fuzz/install/include/cppcheck/ \
 && cp -a /fuzz/build/lib/libcppcheck-core* /fuzz/install/lib/ || true
