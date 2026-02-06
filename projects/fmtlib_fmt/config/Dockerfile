ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (ensure cmake and ninja are present)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build fmt as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DFMT_TEST=OFF \
    -DFMT_FUZZ=OFF \
    -DFMT_DOC=OFF
RUN cmake --build build --target install
