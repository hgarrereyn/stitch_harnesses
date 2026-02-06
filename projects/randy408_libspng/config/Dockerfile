ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libz-dev \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to fuzzer-friendly wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSPNG_SHARED=OFF \
    -DSPNG_STATIC=ON \
    -DBUILD_EXAMPLES=OFF \
 && cmake --build build --target install
