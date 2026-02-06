ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install fastfetch and a static lib for fuzzing
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build with minimal optional deps to avoid system libs
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_FLASHFETCH=OFF \
    -DENABLE_VULKAN=OFF \
    -DENABLE_WAYLAND=OFF \
    -DENABLE_XCB_RANDR=OFF \
    -DENABLE_XRANDR=OFF \
    -DENABLE_DRM=OFF \
    -DENABLE_DRM_AMDGPU=OFF \
    -DENABLE_GIO=OFF \
    -DENABLE_DCONF=OFF \
    -DENABLE_DBUS=OFF \
    -DENABLE_SQLITE3=OFF \
    -DENABLE_RPM=OFF \
    -DENABLE_IMAGEMAGICK7=OFF \
    -DENABLE_IMAGEMAGICK6=OFF \
    -DENABLE_CHAFA=OFF \
    -DENABLE_EGL=OFF \
    -DENABLE_GLX=OFF \
    -DENABLE_OPENCL=OFF \
    -DENABLE_FREETYPE=OFF \
    -DENABLE_PULSE=OFF \
    -DENABLE_DDCUTIL=OFF \
    -DENABLE_ELF=OFF \
    -DENABLE_THREADS=OFF \
    -DENABLE_ZLIB=OFF \
    -DENABLE_LIBZFS=OFF \
    -DENABLE_DIRECTX_HEADERS=OFF \
    -DENABLE_SYSTEM_YYJSON=OFF \
    -DBINARY_LINK_TYPE=dlopen
RUN cmake --build /fuzz/build --target install -j$(nproc)

# Create a static archive from the OBJECT library objects
RUN mkdir -p /fuzz/install/lib && \
    sh -lc 'set -e; objs=$(find /fuzz/build/CMakeFiles/libfastfetch.dir -name "*.o"); \
            [ -n "$objs" ] && ar rcs /fuzz/install/lib/libfastfetch.a $objs || exit 1'

# Install headers (public entry is fastfetch.h but it includes many internal headers)
# Copy all header files from source tree and generated headers from build tree
RUN mkdir -p /fuzz/install/include/fastfetch && \
    cd /fuzz/src/src && \
    find . -type f -name "*.h" | while read -r f; do \
        install -D "$f" "/fuzz/install/include/fastfetch/$f"; \
    done && \
    install -D /fuzz/build/fastfetch_config.h /fuzz/install/include/fastfetch/fastfetch_config.h && \
    install -D /fuzz/build/fastfetch_datatext.h /fuzz/install/include/fastfetch/fastfetch_datatext.h && \
    install -D /fuzz/build/logo_builtin.h /fuzz/install/include/fastfetch/logo_builtin.h
