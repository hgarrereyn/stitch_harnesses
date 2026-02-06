ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and libc++ for C++20 <format>
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    libhidapi-dev \
    pkg-config \
    libc++-17-dev \
    libc++abi-17-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install HeadsetControl (static library)
WORKDIR /fuzz/src

RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBRARY=OFF \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_CXX_FLAGS="-stdlib=libc++"

RUN cmake --build /fuzz/build --target install -j$(nproc)
