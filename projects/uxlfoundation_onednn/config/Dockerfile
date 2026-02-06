ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static CPU-only oneDNN
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DDNNL_LIBRARY_TYPE=STATIC \
    -DDNNL_CPU_RUNTIME=SEQ \
    -DDNNL_GPU_RUNTIME=NONE \
    -DDNNL_BUILD_EXAMPLES=OFF \
    -DDNNL_BUILD_TESTS=OFF \
    -DDNNL_INSTALL_MODE=DEFAULT
RUN cmake --build . --target install --config Release
