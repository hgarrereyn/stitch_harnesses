ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal extra tools
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build pkg-config && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use fuzzer compiler wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure, build, and install CLI11 as a precompiled static library and install all headers (including impl)
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCLI11_PRECOMPILED=ON \
    -DCLI11_FULL_INSTALL=ON \
    -DCLI11_BUILD_TESTS=OFF \
    -DCLI11_BUILD_EXAMPLES=OFF \
    -DCLI11_BUILD_DOCS=OFF \
    -DCLI11_INSTALL=ON && \
    cmake --build build --target install
