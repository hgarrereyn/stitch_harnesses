ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build civetweb as static libs, install to /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCIVETWEB_ENABLE_CXX=ON \
    -DCIVETWEB_ENABLE_SERVER_EXECUTABLE=OFF \
    -DCIVETWEB_BUILD_TESTING=OFF \
    -DCIVETWEB_ENABLE_SSL=ON \
    -DCIVETWEB_ENABLE_SSL_DYNAMIC_LOADING=ON \
 && cmake --build /fuzz/build --target install -j
