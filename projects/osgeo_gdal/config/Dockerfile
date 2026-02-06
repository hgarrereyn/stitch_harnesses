ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build deps and common libraries used by GDAL core
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake make ninja-build pkg-config \
    libsqlite3-dev zlib1g-dev libexpat1-dev \
    libjpeg-turbo8-dev libpng-dev libzstd-dev liblzma-dev libdeflate-dev \
    libtiff-dev libproj-dev libcurl4-gnutls-dev libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build GDAL statically with minimal drivers
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_APPS=OFF \
    -DGDAL_ENABLE_PLUGINS=OFF \
    -DGDAL_ENABLE_PLUGINS_NO_DEPS=OFF \
    -DGDAL_BUILD_OPTIONAL_DRIVERS=OFF \
    -DOGR_BUILD_OPTIONAL_DRIVERS=OFF

RUN cmake --build build -j$(nproc)
RUN cmake --install build
