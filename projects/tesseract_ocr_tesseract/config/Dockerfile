ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libleptonica-dev \
    libpng-dev \
    libjpeg-turbo8-dev \
    libtiff-dev \
    zlib1g-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=OFF \
    -DBUILD_TRAINING_TOOLS=OFF \
    -DOPENMP_BUILD=OFF \
    -DSW_BUILD=OFF \
    -DDISABLE_ARCHIVE=ON \
    -DDISABLE_CURL=ON \
    -DGRAPHICS_DISABLED=ON \
    -DENABLE_UNITY_BUILD=ON \
    -DENABLE_PRECOMPILED_HEADERS=OFF
RUN cmake --build /fuzz/build --target install -j
