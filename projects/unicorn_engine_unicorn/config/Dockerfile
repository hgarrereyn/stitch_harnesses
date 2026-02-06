ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    python3 \
  && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Unicorn (static-only)
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DUNICORN_INSTALL=ON \
    -DUNICORN_LEGACY_STATIC_ARCHIVE=ON \
 && cmake --build /fuzz/build -j \
 && cmake --install /fuzz/build
