ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies for OpenVDB core
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    wget \
    gpg \
    ninja-build \
    libtbb-dev \
    libblosc-dev \
    zlib1g-dev \
    libboost-iostreams-dev \
    && rm -rf /var/lib/apt/lists/*

# Install a recent CMake (>=3.24) from Kitware APT repo
RUN wget -qO /tmp/kitware.sh https://apt.kitware.com/kitware-archive.sh \
    && bash /tmp/kitware.sh \
    && rm -f /tmp/kitware.sh \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install only the core static OpenVDB library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DOPENVDB_BUILD_CORE=ON \
    -DOPENVDB_BUILD_BINARIES=OFF \
    -DOPENVDB_BUILD_PYTHON_MODULE=OFF \
    -DOPENVDB_BUILD_AX=OFF \
    -DOPENVDB_BUILD_NANOVDB=OFF \
    -DOPENVDB_CORE_SHARED=OFF \
    -DOPENVDB_CORE_STATIC=ON \
    -DOPENVDB_USE_DELAYED_LOADING=OFF \
    -DUSE_EXPLICIT_INSTANTIATION=OFF \
    -DUSE_EXR=OFF \
    -DUSE_IMATH_HALF=OFF \
    && cmake --build build --parallel \
    && cmake --install build
