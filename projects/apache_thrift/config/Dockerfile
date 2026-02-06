ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
    libboost-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install only the C++ library as static
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure from repository root to ensure CMake modules are found
RUN cmake -G Ninja /fuzz/src \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_COMPILER=OFF \
    -DBUILD_CPP=ON \
    -DBUILD_TUTORIALS=OFF \
    -DWITH_OPENSSL=OFF \
    -DWITH_ZLIB=OFF \
    -DWITH_LIBEVENT=OFF \
    -DWITH_QT5=OFF \
    -DWITH_C_GLIB=OFF \
    -DWITH_JAVA=OFF \
    -DWITH_JAVASCRIPT=OFF \
    -DWITH_NODEJS=OFF \
    -DWITH_PYTHON=OFF

RUN ninja -j"$(nproc)" && ninja install
