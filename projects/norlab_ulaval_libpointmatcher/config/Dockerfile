ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    build-essential \
    cmake \
    ninja-build \
    libeigen3-dev \
    libboost-all-dev \
    libyaml-cpp-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install libnabo from source (not available on all Ubuntu releases)
RUN git clone --depth 1 https://github.com/norlab-ulaval/libnabo.git /tmp/libnabo && \
    cmake -S /tmp/libnabo -B /tmp/libnabo/build \
      -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF && \
    cmake --build /tmp/libnabo/build --target install --config Release && \
    rm -rf /tmp/libnabo

# Configure, build and install libpointmatcher
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_EVALUATIONS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PYTHON_MODULE=OFF

RUN cmake --build build --target install --config Release
