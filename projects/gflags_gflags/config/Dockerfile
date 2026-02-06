ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (ensure cmake/ninja present)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static nothreads variant only
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_gflags_LIB=OFF \
    -DBUILD_gflags_nothreads_LIB=ON \
    -DINSTALL_HEADERS=ON \
    -DINSTALL_STATIC_LIBS=ON

RUN cmake --build /fuzz/build --target install -j
