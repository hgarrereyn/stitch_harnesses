ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies for configuration and headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-pip \
    pkg-config \
    ninja-build \
    libfmt-dev nlohmann-json3-dev \
  && pip3 install --no-cache-dir cmake==3.29.6 \
  && rm -rf /var/lib/apt/lists/*

# Configure Giada (no full build to keep image small/fast)
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_TESTS=OFF \
    /fuzz/src || true

# Install headers for public API consumption
RUN mkdir -p /fuzz/install/include && cp -r /fuzz/src/src /fuzz/install/include/
