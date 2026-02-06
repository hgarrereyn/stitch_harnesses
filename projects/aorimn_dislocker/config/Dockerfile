ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
    git \
    libfuse3-dev \
    ca-certificates \
    wget \
    tar \
 && rm -rf /var/lib/apt/lists/*

# Build and install MbedTLS v3 (required by Dislocker)
WORKDIR /tmp
RUN git clone --depth 1 --branch v3.6.0 --recursive https://github.com/Mbed-TLS/mbedtls.git \
 && cd mbedtls \
 && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=OFF -DBUILD_TESTING=OFF -DENABLE_PROGRAMS=OFF \
 && cmake --build build -j"$(nproc)" \
 && cmake --install build \
 && cd /tmp \
 && rm -rf mbedtls

# Configure, build, and install Dislocker (work around upstream CMake check on 'src' suffix)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN mkdir -p /tmp/proj \
 && cp -a /fuzz/src/. /tmp/proj/ \
 && cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/fuzz/install -DWITH_RUBY=OFF -DCMAKE_BUILD_TYPE=Release -S /tmp/proj -B /tmp/build \
 && cmake --build /tmp/build -j"$(nproc)" \
 && cmake --install /tmp/build

# Ensure headers are available to external builds
RUN mkdir -p /fuzz/install/include \
 && cp -r /fuzz/src/include/* /fuzz/install/include/
