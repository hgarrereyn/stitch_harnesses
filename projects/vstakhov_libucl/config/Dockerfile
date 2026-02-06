ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Configure environment to use gf compilers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/build

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_LUA=OFF \
    -DENABLE_URL_INCLUDE=OFF \
    -DENABLE_URL_SIGN=OFF \
    -DENABLE_UTILS=OFF \
    -DCMAKE_BUILD_TYPE=Release && \
    cmake --build /fuzz/build --target install -j$(nproc)
