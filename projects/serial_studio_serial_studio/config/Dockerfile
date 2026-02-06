ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra deps needed for KissFFT
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build make && rm -rf /var/lib/apt/lists/*

# Build and install KissFFT as a static library
WORKDIR /fuzz/src/lib/KissFFT

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DKISSFFT_STATIC=ON \
    -DKISSFFT_TEST=OFF \
    -DKISSFFT_TOOLS=OFF

RUN cmake --build build -j"$(nproc)"
RUN cmake --install build
