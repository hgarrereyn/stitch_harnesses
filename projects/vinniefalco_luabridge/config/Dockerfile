ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and Lua development package
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    liblua5.4-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and install LuaBridge headers into /fuzz/install
WORKDIR /fuzz/src
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLUABRIDGE_TESTING=OFF \
    -DBUILD_SHARED_LIBS=OFF
RUN cmake --build /fuzz/build --target install -j$(nproc)
