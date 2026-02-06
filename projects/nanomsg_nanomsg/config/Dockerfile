ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    make \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Configure, build static lib, install to /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DNN_STATIC_LIB=ON \
    -DNN_ENABLE_DOC=OFF \
    -DNN_TESTS=OFF \
    -DNN_TOOLS=OFF \
    -DBUILD_SHARED_LIBS=OFF && \
    cmake --build /fuzz/build --parallel && \
    cmake --install /fuzz/build
