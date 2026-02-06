ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build static libavif with minimal dependencies and install to /fuzz/install
RUN cmake -S /fuzz/src -B /tmp/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DAVIF_BUILD_APPS=OFF \
    -DAVIF_BUILD_TESTS=OFF \
    -DAVIF_CODEC_AOM=OFF \
    -DAVIF_CODEC_DAV1D=OFF \
    -DAVIF_CODEC_LIBGAV1=OFF \
    -DAVIF_CODEC_RAV1E=OFF \
    -DAVIF_CODEC_SVT=OFF \
    -DAVIF_LIBYUV=OFF \
    -DAVIF_LIBSHARPYUV=OFF \
    -DAVIF_JPEG=OFF \
    -DAVIF_ZLIBPNG=OFF \
 && cmake --build /tmp/build --parallel \
 && cmake --install /tmp/build
