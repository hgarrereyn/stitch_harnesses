ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    cmake \
    pkg-config \
    ninja-build \
    libssl-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install Abseil (shared) to a local prefix
RUN git clone --depth 1 https://github.com/abseil/abseil-cpp.git /tmp/abseil && \
    cmake -S /tmp/abseil -B /tmp/abseil/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/deps/absl \
      -DBUILD_SHARED_LIBS=ON \
      -DABSL_BUILD_SHARED_LIBS=ON && \
    cmake --build /tmp/abseil/build --parallel && \
    cmake --install /tmp/abseil/build && \
    rm -rf /tmp/abseil

# Configure, build, and install s2geometry
WORKDIR /fuzz/src
RUN cmake -S . -B /tmp/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=ON \
      -DBUILD_TESTS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DCMAKE_PREFIX_PATH=/fuzz/deps/absl && \
    cmake --build /tmp/build --parallel && \
    cmake --install /tmp/build && \
    rm -rf /tmp/build

ENV LD_LIBRARY_PATH=/fuzz/install/lib:/fuzz/deps/absl/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
