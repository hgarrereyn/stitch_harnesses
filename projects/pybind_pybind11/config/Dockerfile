ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and Python development headers required by pybind11
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make build-essential pkg-config \
    python3-dev python3-minimal \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install pybind11 (header-only)
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B . -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPYBIND11_TEST=OFF \
    -DPYBIND11_INSTALL=ON \
    -DPYBIND11_NOPYTHON=ON \
 && cmake --build . --target install
