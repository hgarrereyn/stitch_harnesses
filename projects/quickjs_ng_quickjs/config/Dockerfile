ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config && \
    rm -rf /var/lib/apt/lists/*

# Use fuzzing compiler wrappers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure, build, and install the static library
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DQJS_BUILD_LIBC=ON && \
    cmake --build /fuzz/build --target install -j$(nproc)
