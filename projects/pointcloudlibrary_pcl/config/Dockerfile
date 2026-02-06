ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libeigen3-dev \
    libboost-dev \
    libboost-iostreams-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPCL_SHARED_LIBS=OFF \
    -DPCL_ONLY_CORE_POINT_TYPES=ON \
    -DPCL_ENABLE_SSE=OFF \
    -DPCL_ENABLE_AVX=OFF \
    -DPCL_ENABLE_MARCHNATIVE=OFF \
    -DWITH_OPENMP=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_VTK=OFF \
    -DWITH_QT=NO \
    -DWITH_QHULL=OFF \
    -DWITH_PNG=OFF \
    -DWITH_LIBUSB=OFF \
    -DWITH_PCAP=OFF \
    -DWITH_OPENGL=OFF \
    -DWITH_GLEW=OFF \
    -DBUILD_apps=OFF \
    -DBUILD_examples=OFF \
    -DBUILD_tools=OFF \
    -DBUILD_2d=OFF \
    -DBUILD_common=ON \
    -DBUILD_features=OFF \
    -DBUILD_filters=OFF \
    -DBUILD_geometry=OFF \
    -DBUILD_io=OFF \
    -DBUILD_kdtree=OFF \
    -DBUILD_keypoints=OFF \
    -DBUILD_ml=OFF \
    -DBUILD_octree=OFF \
    -DBUILD_outofcore=OFF \
    -DBUILD_people=OFF \
    -DBUILD_recognition=OFF \
    -DBUILD_registration=OFF \
    -DBUILD_sample_consensus=OFF \
    -DBUILD_search=OFF \
    -DBUILD_segmentation=OFF \
    -DBUILD_simulation=OFF \
    -DBUILD_stereo=OFF \
    -DBUILD_surface=OFF \
    -DBUILD_tracking=OFF \
    -DBUILD_visualization=OFF

RUN cmake --build . --target install -- -v

