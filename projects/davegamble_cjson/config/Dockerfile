ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (cmake is required by this project)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz

# Configure and build static libraries and install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_SHARED_AND_STATIC_LIBS=OFF \
    -DENABLE_CJSON_UTILS=ON \
    -DENABLE_CJSON_TEST=OFF \
    -DENABLE_TARGET_EXPORT=OFF \
    -DENABLE_CUSTOM_COMPILER_FLAGS=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
