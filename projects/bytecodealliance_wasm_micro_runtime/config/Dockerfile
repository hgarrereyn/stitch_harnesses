ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure, build and install static lib
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && cmake --build build -j \
 && cmake --install build
