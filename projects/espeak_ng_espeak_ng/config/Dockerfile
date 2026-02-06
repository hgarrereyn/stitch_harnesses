ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build git \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install espeak-ng
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/build && \
    cmake -S /fuzz/src -B /fuzz/build -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=ON \
      -DENABLE_TESTS=OFF \
    && cmake --build /fuzz/build --target install -j
