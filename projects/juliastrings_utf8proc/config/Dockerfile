ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build dependencies (cmake and ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Use the fuzzing compiler wrappers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz

# Configure, build, and install
RUN cmake -S /fuzz/src -B /fuzz/build \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DUTF8PROC_INSTALL=ON \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  && cmake --build /fuzz/build --target install -- -v
