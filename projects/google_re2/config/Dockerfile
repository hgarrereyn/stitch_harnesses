ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and git
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake make git ca-certificates pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Build and install Abseil from source (new enough for RE2)
WORKDIR /tmp
RUN git clone --depth 1 https://github.com/abseil/abseil-cpp.git abseil && \
    cmake -S abseil -B abseil/build \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_TESTING=OFF -DBUILD_SHARED_LIBS=ON -DABSL_PROPAGATE_CXX_STD=ON && \
    cmake --build abseil/build -j && \
    cmake --install abseil/build && \
    rm -rf /tmp/abseil

# Configure, build, and install RE2
WORKDIR /fuzz/src
RUN cmake -S . -B build \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=ON \
      -DRE2_TEST=OFF -DRE2_BENCHMARK=OFF \
      -DCMAKE_PREFIX_PATH=/fuzz/install \
    && cmake --build build -j \
    && cmake --install build
