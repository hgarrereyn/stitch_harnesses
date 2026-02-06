ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install static library
RUN cmake -S /fuzz/src -B /tmp/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DMANIFOLD_TEST=OFF \
    -DMANIFOLD_PYBIND=OFF \
    -DMANIFOLD_CBIND=OFF \
    -DMANIFOLD_JSBIND=OFF \
    -DMANIFOLD_EXPORT=OFF \
    -DMANIFOLD_PAR=OFF \
    -DMANIFOLD_CROSS_SECTION=OFF \
    -DMANIFOLD_DOWNLOADS=OFF \
 && cmake --build /tmp/build --target install -j$(nproc) \
 && rm -rf /tmp/build
