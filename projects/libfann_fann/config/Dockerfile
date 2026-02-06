ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install FANN into /fuzz/install using the fuzzing compilers
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B . \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DDISABLE_PARALLEL_FANN=ON \
 && cmake --build . --target install -j
