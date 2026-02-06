ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake make pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build with CMake
RUN cmake -S . -B build \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_PROGRAMS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_TESTING=OFF \
      -DENABLE_EXTERNAL_LIBS=OFF \
      -DENABLE_MPEG=OFF \
    && cmake --build build -j \
    && cmake --install build
