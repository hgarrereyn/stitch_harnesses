ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install zlib (vendored in ReactOS) as a static library
# Source is already in /fuzz/src

# Install required build tools (cmake, ninja)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install \
    BUILD_DIR=/fuzz/build \
    SRC_DIR=/fuzz/src

# Configure, build, and "install" (copy) the library and headers
RUN cmake -S "$SRC_DIR/sdk/lib/3rdparty/zlib" -B "$BUILD_DIR" -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DREACTOS_SOURCE_DIR="$SRC_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
 && cmake --build "$BUILD_DIR" --target zlibhost -j \
 && mkdir -p "$INSTALL_PREFIX/lib" "$INSTALL_PREFIX/include" \
 && cp "$BUILD_DIR/libzlibhost.a" "$INSTALL_PREFIX/lib/" \
 && cp "$SRC_DIR/sdk/include/reactos/libs/zlib/"*.h "$INSTALL_PREFIX/include/"
