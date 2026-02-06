ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    ca-certificates unzip \
 && rm -rf /var/lib/apt/lists/*

# Use libAFL compiler wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Configure, build, and install Yoga
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_FUZZ_TESTS=OFF \
    -G Ninja && \
    cmake --build /fuzz/build --target install -j$(nproc)
