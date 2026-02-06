ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: tools, BLAS/LAPACK, OpenMP (matching clang-17)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-pip \
    make \
    ninja-build \
    libopenblas-dev \
    liblapack-dev \
    libomp-17-dev \
 && rm -rf /var/lib/apt/lists/*

# New enough CMake (>=3.24) via pip
RUN python3 -m pip install --no-cache-dir "cmake>=3.24"

# Configure, build and install Faiss (CPU-only, static)
WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DFAISS_ENABLE_GPU=OFF \
    -DFAISS_ENABLE_PYTHON=OFF \
    -DFAISS_ENABLE_EXTRAS=OFF \
    -DFAISS_ENABLE_C_API=OFF \
    -DFAISS_ENABLE_MKL=OFF \
    -DFAISS_OPT_LEVEL=generic \
 && cmake --build build --target install -j$(nproc)
