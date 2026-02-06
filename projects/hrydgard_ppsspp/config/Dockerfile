ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install extra build dependencies (OpenGL ES/EGL headers)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    ca-certificates \
    python3 \
    ninja-build \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build PPSSPP libraries only (no SDL/Qt app)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLIBRETRO=ON \
    -DHEADLESS=OFF \
    -DUSING_QT_UI=OFF \
    -DUSE_SYSTEM_LIBSDL2=OFF \
    -DUSE_FFMPEG=OFF \
    -DUSE_SYSTEM_LIBPNG=OFF \
    -DUNITTEST=OFF \
    -DATLAS_TOOL=OFF \
    -DUSING_GLES2=ON \
    -DUSING_EGL=ON \
    -DUSING_X11_VULKAN=OFF \
    -DUSE_WAYLAND_WSI=OFF \
    -DVULKAN=OFF \
 && cmake --build /fuzz/build --parallel

# Install: copy static libs and headers to /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/Core /fuzz/install/include/Common && \
    cp -a /fuzz/build/lib/*.a /fuzz/install/lib/ && \
    cp -a /fuzz/build/ppsspp_libretro*.so /fuzz/install/lib/ || true && \
    cp -a /fuzz/src/Core/Core.h /fuzz/src/Core/System.h /fuzz/src/Core/Instance.h /fuzz/src/Core/Config.h /fuzz/install/include/Core/ && \
    cp -a /fuzz/src/Common /fuzz/install/include/
