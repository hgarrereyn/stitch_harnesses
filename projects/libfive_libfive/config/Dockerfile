ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    make \
    ninja-build \
    pkg-config \
    libeigen3-dev \
    libpng-dev \
    libboost-all-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libfive (library only)
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_STUDIO_APP=OFF \
    -DBUILD_GUILE_BINDINGS=OFF \
    -DBUILD_PYTHON_BINDINGS=OFF
RUN cmake --build /fuzz/build --target install -j
