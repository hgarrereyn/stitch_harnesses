ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libgd statically
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DENABLE_GD_FORMATS=OFF \
    -DENABLE_PNG=OFF \
    -DENABLE_LIQ=OFF \
    -DENABLE_JPEG=OFF \
    -DENABLE_TIFF=OFF \
    -DENABLE_ICONV=OFF \
    -DENABLE_XPM=OFF \
    -DENABLE_FREETYPE=OFF \
    -DENABLE_FONTCONFIG=OFF \
    -DENABLE_WEBP=OFF \
    -DENABLE_HEIF=OFF \
    -DENABLE_AVIF=OFF \
    -DENABLE_RAQM=OFF \
    -DENABLE_CPP=ON
RUN cmake --build build --target install -j$(nproc)
