ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src
RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DMATPLOTPP_BUILD_EXAMPLES=OFF \
    -DMATPLOTPP_BUILD_TESTS=OFF \
    -DMATPLOTPP_BUILD_SHARED_LIBS=OFF \
    -DMATPLOTPP_BUILD_INSTALLER=ON
RUN cmake --build /fuzz/build --target install --config Release --parallel
