ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed by this project
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      make \
      pkg-config \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    CMAKE_BUILD_TYPE=Release \
    INSTALL_PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Configure, build static library only, and install
RUN cmake -S . -B build \
      -DBUILD_TESTING=OFF \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
      -DCMAKE_C_COMPILER=${CC} \
      -DCMAKE_CXX_COMPILER=${CXX} \
    && cmake --build build -j$(nproc) \
    && cmake --install build
