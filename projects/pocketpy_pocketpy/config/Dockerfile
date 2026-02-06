ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Build static library with CMake
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz

RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPK_BUILD_SHARED_LIB=OFF \
    -DPK_BUILD_STATIC_LIB=ON \
    -DPK_BUILD_STATIC_MAIN=OFF \
    -DPK_ENABLE_MIMALLOC=OFF

RUN cmake --build /fuzz/build -j

# Manually install since upstream doesn't provide install rules
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp /fuzz/build/libpocketpy.a /fuzz/install/lib/ \
    && cp -r /fuzz/src/include/* /fuzz/install/include/
