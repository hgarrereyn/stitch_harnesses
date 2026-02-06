ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and install the header-only library and its embedded nlohmann/json
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTING=OFF \
    -DINJA_INSTALL=ON \
    -DINJA_USE_EMBEDDED_JSON=ON \
 && cmake --build build --target install
