ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config build-essential \
    && rm -rf /var/lib/apt/lists/*

# Configure and build Highway as static libs, install to /fuzz/install
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DHWY_ENABLE_TESTS=OFF \
    -DHWY_ENABLE_EXAMPLES=OFF \
    -DHWY_ENABLE_INSTALL=ON \
    -DHWY_WARNINGS_ARE_ERRORS=OFF && \
    cmake --build /fuzz/build --target install -j$(nproc)
