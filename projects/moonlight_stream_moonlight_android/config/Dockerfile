ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake ninja-build pkg-config libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Initialize submodules to fetch moonlight-common-c
WORKDIR /fuzz/src
RUN git submodule update --init --recursive

# Build and install moonlight-common-c as a static library
WORKDIR /fuzz/src/app/src/main/jni/moonlight-core/moonlight-common-c

# Try CMake first; if it doesn't install headers, fall back to manual install
RUN mkdir -p build && cd build \
 && CC=stitch_libafl_cc CXX=stitch_libafl_cxx cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    .. \
 && ninja \
 && ninja install || true

# Ensure headers and static libs are installed even if cmake install didn't
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    if [ -d include ]; then cp -a include/*.h /fuzz/install/include/ || true; fi && \
    if [ -d src ]; then cp -a src/*.h /fuzz/install/include/ || true; fi && \
    find . -name "*.a" -exec cp {} /fuzz/install/lib/ \; || true

WORKDIR /fuzz/src
