ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    make \
 && rm -rf /var/lib/apt/lists/*

# Build RenderDoc core library only (no GUI, no drivers)
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_GL=OFF \
    -DENABLE_GLES=OFF \
    -DENABLE_EGL=OFF \
    -DENABLE_VULKAN=OFF \
    -DENABLE_METAL=OFF \
    -DENABLE_RENDERDOCCMD=OFF \
    -DENABLE_QRENDERDOC=OFF \
    -DENABLE_PYRENDERDOC=OFF \
    -DENABLE_XLIB=OFF \
    -DENABLE_XCB=OFF \
    /fuzz/src

RUN cmake --build . --target install -- -v
