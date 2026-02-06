ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    zlib1g-dev \
    libcurl4-openssl-dev \
    libfontconfig1-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libxinerama-dev \
    libxcursor-dev \
    libgl1-mesa-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build Cinder as a static library, disabling heavy subsystems
WORKDIR /fuzz/src
RUN cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCINDER_DISABLE_AUDIO=ON \
    -DCINDER_DISABLE_VIDEO=ON \
    -DCINDER_TARGET=linux \
    -DCINDER_TARGET_GL=ogl
RUN cmake --build build -j

# Install headers and static library into /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r include/* /fuzz/install/include/ \
 && ARCH=$(uname -m) \
 && LIBPATH="/fuzz/src/lib/linux/${ARCH}/ogl/Release" \
 && cp "$LIBPATH"/libcinder.a /fuzz/install/lib/
