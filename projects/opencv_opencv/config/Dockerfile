ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and system zlib for linking
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    cmake \
    ninja-build \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build a minimal static OpenCV (core, imgproc)
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_LIST=core,imgproc \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_JAVA=OFF \
    -DBUILD_opencv_python=OFF \
    -DWITH_ITT=OFF \
    -DWITH_IPP=OFF \
    -DWITH_TBB=OFF \
    -DWITH_OPENCL=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_GSTREAMER=OFF \
    -DWITH_1394=OFF \
    -DWITH_V4L=OFF \
    -DWITH_GTK=OFF \
    -DWITH_QT=OFF \
    -DOPENCV_FORCE_3RDPARTY_BUILD=ON \
 && cmake --build build -j $(nproc) \
 && cmake --install build
