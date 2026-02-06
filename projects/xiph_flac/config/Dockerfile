ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (ensure cmake present in minimal images)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install static libraries only
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B . \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_PROGRAMS=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_CXXLIBS=OFF \
    -DWITH_OGG=OFF \
    -DINSTALL_CMAKE_CONFIG_MODULE=OFF \
    -DINSTALL_PKGCONFIG_MODULES=OFF \
    -DINSTALL_MANPAGES=OFF \
    -DCMAKE_C_FLAGS="-U FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION" \
    -DCMAKE_CXX_FLAGS="-U FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
RUN cmake --build . --config Release --target install
