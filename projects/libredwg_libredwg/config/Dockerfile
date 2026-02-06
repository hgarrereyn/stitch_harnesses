ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static lib with minimal features
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLIBREDWG_LIBONLY=ON \
    -DLIBREDWG_DISABLE_WRITE=ON \
    -DLIBREDWG_DISABLE_JSON=ON \
    -DDISABLE_WERROR=ON
RUN cmake --build build --target install --config Release
