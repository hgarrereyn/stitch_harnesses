ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and runtime dependencies for CPU backend
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libfftw3-dev liblapacke-dev libopenblas-dev \
    libboost-all-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DAF_BUILD_CPU=ON \
    -DAF_BUILD_CUDA=OFF \
    -DAF_BUILD_OPENCL=OFF \
    -DAF_BUILD_ONEAPI=OFF \
    -DAF_BUILD_UNIFIED=OFF \
    -DAF_BUILD_EXAMPLES=OFF \
    -DAF_BUILD_DOCS=OFF \
    -DBUILD_TESTING=OFF \
    -DAF_WITH_IMAGEIO=OFF \
    -DAF_WITH_LOGGING=OFF \
    -DAF_STACKTRACE_TYPE=None \
    -DAF_COMPUTE_LIBRARY="FFTW/LAPACK/BLAS" \
    -DAF_WITH_CPUID=OFF && \
    cmake --build build --target install -j$(nproc)
