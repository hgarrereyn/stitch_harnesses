ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (include cmake in case base image lacks it)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    yasm nasm perl pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure and build static libaom
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja -S /fuzz/src -B /fuzz/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DENABLE_TESTS=0 \
      -DENABLE_EXAMPLES=0 \
      -DENABLE_DOCS=0 \
      -DCONFIG_WEBM_IO=0 \
    && cmake --build /fuzz/build --target install -j"$(nproc)"
