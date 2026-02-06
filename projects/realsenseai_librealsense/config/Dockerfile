ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libusb-1.0-0-dev \
    ca-certificates \
    git \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_UNIT_TESTS=OFF \
    -DBUILD_GLSL_EXTENSIONS=OFF \
    -DBUILD_PYTHON_BINDINGS=OFF \
    -DBUILD_WITH_CUDA=OFF \
    -DFORCE_RSUSB_BACKEND=ON \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    /fuzz/src
RUN cmake --build . --target install -- -v
