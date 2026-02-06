ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake ninja-build make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build OpenSubdiv (CPU-only, static libs)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/fuzz/install \
    -D BUILD_SHARED_LIBS=OFF \
    -D NO_DOC=1 -D NO_EXAMPLES=1 -D NO_TUTORIALS=1 -D NO_REGRESSION=1 -D NO_PTEX=1 \
    -D NO_OMP=1 -D NO_TBB=1 -D NO_CUDA=1 -D NO_OPENCL=1 -D NO_CLEW=1 -D NO_OPENGL=1 -D NO_METAL=1 \
    -D NO_MACOS_FRAMEWORK=1
RUN cmake --build build --target install -- -v
