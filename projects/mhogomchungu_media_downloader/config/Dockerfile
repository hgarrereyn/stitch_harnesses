ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    qtbase5-dev \
    qtbase5-dev-tools \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

RUN cmake -S /fuzz/src -B /build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_WITH_QT6=OFF \
    -DCMAKE_BUILD_TYPE=Release \
 && cmake --build /build -j \
 && cmake --install /build \
 && mkdir -p /fuzz/install/include/media-downloader \
 && cp /fuzz/src/src/utils/*.hpp /fuzz/install/include/media-downloader/
