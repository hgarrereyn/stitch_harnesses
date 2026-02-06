ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed to build facil.io (build tools + OpenSSL)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Build facil.io as a static library using the fuzzing compiler wrappers
WORKDIR /fuzz/src/facil.io
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      .. && \
    ninja

# "Install" headers and the static library manually (no install target provided)
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r /fuzz/src/facil.io/lib/facil /fuzz/install/include/ && \
    cp /fuzz/src/facil.io/build/libfacil.io.a /fuzz/install/lib/
