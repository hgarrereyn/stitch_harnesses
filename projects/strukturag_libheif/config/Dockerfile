ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libheif (static, minimal, no external codecs/plugins)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_PLUGIN_LOADING=OFF \
    -DWITH_LIBSHARPYUV=OFF \
    -DWITH_EXAMPLES=OFF \
    -DWITH_GDK_PIXBUF=OFF \
    -DBUILD_DOCUMENTATION=OFF \
    -DBUILD_TESTING=OFF \
    -DWITH_HEADER_COMPRESSION=OFF \
    -DWITH_UNCOMPRESSED_CODEC=OFF \
    -DWITH_LIBDE265=OFF \
    -DWITH_X265=OFF \
    -DWITH_KVAZAAR=OFF \
    -DWITH_UVG266=OFF \
    -DWITH_VVDEC=OFF \
    -DWITH_VVENC=OFF \
    -DWITH_OpenH264_DECODER=OFF \
    -DWITH_DAV1D=OFF \
    -DWITH_AOM_DECODER=OFF \
    -DWITH_AOM_ENCODER=OFF \
    -DWITH_SvtEnc=OFF \
    -DWITH_RAV1E=OFF \
    -DWITH_JPEG_DECODER=OFF \
    -DWITH_JPEG_ENCODER=OFF \
    -DWITH_OpenJPEG_DECODER=OFF \
    -DWITH_OpenJPEG_ENCODER=OFF \
    -DWITH_OPENJPH_ENCODER=OFF \
    -DWITH_WEBCODECS=OFF \
    . && \
    cmake --build build -j && \
    cmake --install build
