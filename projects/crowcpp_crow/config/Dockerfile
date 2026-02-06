ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        libasio-dev \
        cmake \
        ninja-build \
        make \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure and install Crow (header-only)
WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCROW_BUILD_EXAMPLES=OFF \
    -DCROW_BUILD_TESTS=OFF \
    -DCROW_INSTALL=ON

RUN cmake --build /fuzz/build --target install --config Release
