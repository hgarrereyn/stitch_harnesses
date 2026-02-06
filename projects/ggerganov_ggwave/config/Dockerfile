ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake may be absent in base image)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure, build, install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DGGWAVE_BUILD_EXAMPLES=OFF \
    -DGGWAVE_BUILD_TESTS=OFF \
    -DGGWAVE_SUPPORT_SDL2=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
