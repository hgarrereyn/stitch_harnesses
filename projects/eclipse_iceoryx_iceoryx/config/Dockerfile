ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libacl1-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build and install iceoryx components: platform, hoofs, posh
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install \
    SRC_DIR=/fuzz/src \
    BUILD_DIR=/fuzz/build \
    CMAKE_GENERATOR=Ninja

# iceoryx_platform
RUN cmake -S "$SRC_DIR/iceoryx_platform" -B "$BUILD_DIR/platform" -G "$CMAKE_GENERATOR" \
    -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build "$BUILD_DIR/platform" --target install -j

# iceoryx_hoofs
RUN cmake -S "$SRC_DIR/iceoryx_hoofs" -B "$BUILD_DIR/hoofs" -G "$CMAKE_GENERATOR" \
    -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} \
    -DBUILD_SHARED_LIBS=OFF \
 && cmake --build "$BUILD_DIR/hoofs" --target install -j

# iceoryx_posh
RUN cmake -S "$SRC_DIR/iceoryx_posh" -B "$BUILD_DIR/posh" -G "$CMAKE_GENERATOR" \
    -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} \
    -DBUILD_SHARED_LIBS=OFF \
    -DDOWNLOAD_TOML_LIB=ON -DTOML_CONFIG=ON \
 && cmake --build "$BUILD_DIR/posh" --target install -j
