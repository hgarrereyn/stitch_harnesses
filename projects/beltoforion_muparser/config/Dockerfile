ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure env to use the fuzzing compiler wrappers
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure, build and install static lib
RUN cmake -S /fuzz/src -B /tmp/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_OPENMP=OFF \
    -DENABLE_SAMPLES=OFF \
    -DBUILD_TESTING=OFF \
 && cmake --build /tmp/build --target install -j $(nproc) \
 && rm -rf /tmp/build
