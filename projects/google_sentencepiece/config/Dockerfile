ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build pkg-config && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build with CMake (static only)
RUN cmake -S . -B build \
      -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DSPM_ENABLE_SHARED=OFF \
      -DSPM_ABSL_PROVIDER=internal \
      -DSPM_PROTOBUF_PROVIDER=internal \
    && cmake --build build --target install -- -v
