ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies and cmake for building poppler (cpp API only)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libfreetype6-dev \
    libfontconfig1-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static poppler with only the C++ wrapper
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_UTILS=OFF \
    -DENABLE_GLIB=OFF \
    -DENABLE_QT5=OFF \
    -DENABLE_QT6=OFF \
    -DENABLE_NSS3=OFF \
    -DENABLE_GPGME=OFF \
    -DENABLE_LIBCURL=OFF \
    -DENABLE_LCMS=OFF \
    -DENABLE_LIBTIFF=OFF \
    -DENABLE_DCTDECODER=none \
    -DENABLE_LIBOPENJPEG=none \
    -DENABLE_BOOST=OFF \
    -DFONT_CONFIGURATION=fontconfig \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx && \
    cmake --build /fuzz/build --target install -j$(nproc)
