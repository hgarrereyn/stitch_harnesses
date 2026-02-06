ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja) in case base doesn't provide them
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install dlib as a static library
WORKDIR /fuzz/src/dlib
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DDLIB_NO_GUI_SUPPORT=ON \
    -DDLIB_USE_CUDA=OFF \
    -DDLIB_USE_BLAS=OFF \
    -DDLIB_USE_LAPACK=OFF \
    -DDLIB_GIF_SUPPORT=OFF \
    -DDLIB_WEBP_SUPPORT=OFF \
    -DDLIB_JXL_SUPPORT=OFF \
    -DDLIB_LINK_WITH_SQLITE3=OFF \
    -DDLIB_USE_FFMPEG=OFF
RUN cmake --build build --target install --config Release
