ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for qpdf (cmake, zlib, libjpeg) and pkg-config
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        pkg-config \
        zlib1g-dev \
        libjpeg-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install qpdf as static library with native crypto only
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DUSE_IMPLICIT_CRYPTO=OFF \
    -DREQUIRE_CRYPTO_NATIVE=ON \
    -DINSTALL_PKGCONFIG=ON \
    -DINSTALL_CMAKE_PACKAGE=ON \
 && cmake --build build -j \
 && cmake --install build
