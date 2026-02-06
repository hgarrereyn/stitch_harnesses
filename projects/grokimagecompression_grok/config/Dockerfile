ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install Grok (static core only)
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DGRK_BUILD_CODEC=OFF \
    -DGRK_BUILD_CORE_EXAMPLES=OFF \
    -DGRK_ENABLE_EXIFTOOL=OFF \
    -DGRK_ENABLE_LIBCURL=OFF \
    -DGRK_BUILD_LIBPNG=OFF \
    -DGRK_BUILD_LIBTIFF=OFF \
    -DGRK_BUILD_JPEG=OFF \
    -DGRK_BUNDLE_STATIC_CORE=ON \
 && cmake --build build -j \
 && cmake --install build
