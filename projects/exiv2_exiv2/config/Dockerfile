ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    libfmt-dev \
    libexpat1-dev \
    zlib1g-dev \
    libbrotli-dev \
    libinih-dev \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install exiv2
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DEXIV2_ENABLE_NLS=OFF \
    -DEXIV2_ENABLE_WEBREADY=OFF \
    -DEXIV2_ENABLE_BMFF=OFF
RUN cmake --build /fuzz/build --parallel
RUN cmake --install /fuzz/build
