ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and Python for newer CMake
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-pip \
    ninja-build \
    make \
    build-essential \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Install a recent CMake (>=3.28)
RUN pip3 install --no-cache-dir --upgrade cmake

# Build and install SOEM
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSOEM_BUILD_SAMPLES=OFF

RUN cmake --build build --target install --config RelWithDebInfo
